/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Data.SqlClient;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;


public partial class Promote : BasePage
{
    public Promote()
    {
		Page.Init += new System.EventHandler( Page_Init );
    }

    private DataSet GetDataSet( SqlConnection Connection, int BranchConfigID, int AccessMin, int AccessMax, int Count )
    {
        DataSet SetOfData = new DataSet();

        string ParentString = "SELECT TOP ( " + Count.ToString() + " ) BuildLog.ID, BuildLog.BuildLabel, BuildLog.BuildStarted FROM BuildLog " +
			"JOIN Commands ON CommandID = Commands.ID " +
			"WHERE ( BuildLog.BuildLabel IS NOT NULL AND Commands.IsPromotable = 1 AND BuildLog.BranchConfigID = " + BranchConfigID.ToString() + " ) " +
			"ORDER BY BuildLog.BuildStarted DESC";
        SqlDataAdapter ParentCommand = new SqlDataAdapter( ParentString, Connection );
        ParentCommand.Fill( SetOfData, "BuildLabels" );

        SqlDataAdapter ChildCommand = new SqlDataAdapter( "SELECT C.Description, C.ID AS CommandID, B.ID, B.BuildLabel FROM Commands AS C CROSS JOIN ( " + ParentString + " ) AS B " +
			"WHERE ( C.Access >= " + AccessMin.ToString() + " AND C.Access <= " + AccessMax.ToString() + " ) ORDER BY C.Access", Connection );
        ChildCommand.Fill( SetOfData, "Buttons" );

        SetOfData.Relations.Add( "PseudoRelation", SetOfData.Tables["BuildLabels"].Columns["ID"], SetOfData.Tables["Buttons"].Columns["ID"] );

        return ( SetOfData );
    }

    protected void Page_Load( object sender, EventArgs e )
    {
        string LoggedOnUser = Context.User.Identity.Name;
        string MachineName = Context.Request.UserHostName;

        Label_Welcome.Text = "Welcome \"" + LoggedOnUser + "\" running on \"" + MachineName + "\"";

		using( SqlConnection Connection = new SqlConnection( ConfigurationManager.ConnectionStrings["BuilderConnectionString"].ConnectionString ) )
		{
			Connection.Open();

			string UE3Query = "SELECT LastGoodChangeList FROM Commands WHERE ( Description = 'Send QA Build Changes' )";
			int StartChangeList = ReadInt( Connection, UE3Query );
			UE3Query = "SELECT LastGoodChangeList FROM Commands WHERE ( Description = 'Promote QA Build' )";
			int EndChangeList = ReadInt( Connection, UE3Query );
			Label_UE3ChangesRange.Text = "Current range for QA changes is from " + StartChangeList.ToString() + " to " + EndChangeList.ToString();

			string UE4Query = "SELECT LastGoodChangeList FROM Commands WHERE ( Description = 'Send UE4 QA Build Changes' )";
			int UE4StartChangeList = ReadInt( Connection, UE4Query );
			UE4Query = "SELECT LastGoodChangeList FROM Commands WHERE ( Description = 'Promote UE4 QA Build' )";
			int UE4EndChangeList = ReadInt( Connection, UE4Query );
			Label_UE4ChangesRange.Text = "Current range for UE4 QA changes is from " + UE4StartChangeList.ToString() + " to " + UE4EndChangeList.ToString();

			DataSet UE3 = GetDataSet( Connection, 1, 3000, 3099, 10 );
			UnrealEngine3Repeater.DataSource = UE3.Tables["BuildLabels"];

			DataSet UE4 = GetDataSet(Connection, 184, 2000, 2099, 5);
			UE4_Repeater.DataSource = UE4.Tables["BuildLabels"];

			DataSet UE4Pretest = GetDataSet( Connection, 198, 2100, 2199, 5 );
			UE4Pretest_Repeater.DataSource = UE4Pretest.Tables["BuildLabels"];

			DataSet Exodus = GetDataSet( Connection, 193, 3100, 3199, 5 );
			UnrealEngine3ExodusRepeater.DataSource = Exodus.Tables["BuildLabels"];

			DataSet ProjectSword = GetDataSet( Connection, 65, 3300, 3399, 5 );
			UnrealEngine3ProjectSwordRepeater.DataSource = ProjectSword.Tables["BuildLabels"];

			DataSet UE3QA = GetDataSet( Connection, 1, 3900, 3909, 10 );
			UnrealEngine3QARepeater.DataSource = UE3QA.Tables["BuildLabels"];

			DataSet UE4QA = GetDataSet( Connection, 184, 3910, 3919, 10 );
			UnrealEngine4QARepeater.DataSource = UE4QA.Tables["BuildLabels"];

			Page.DataBind();
			Connection.Close();
		}
    }

    private void Page_Init( object sender, EventArgs e )
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        this.Load += new System.EventHandler( this.Page_Load );
    }

    private void BuilderDBRepeater_PromoteItemCommand( RepeaterCommandEventArgs e, string VariableName, int BranchConfigID )
    {
        if( e.Item != null )
        {
			using( SqlConnection Connection = new SqlConnection( ConfigurationManager.ConnectionStrings["BuilderConnectionString"].ConnectionString ) )
			{
				Connection.Open();

				int CommandID = Int32.Parse( ( string )e.CommandName );
				string BuildLabel = ( string )e.CommandArgument;

				// Find the command id that matches the description
				if( CommandID != 0 )
				{
					// Set the latest build variable
					string CommandString = "UPDATE Variables SET Value = '" + BuildLabel + "' WHERE ( Variable = '" + VariableName + "' AND BranchConfigID = " + BranchConfigID + " )";
					Update( Connection, CommandString );

					// Trigger the build promotion
					string User = Context.User.Identity.Name;
					int Offset = User.LastIndexOf( '\\' );
					if( Offset >= 0 )
					{
						User = User.Substring( Offset + 1 );
					}

					CommandString = "UPDATE Commands SET Pending = 1, Operator = '" + User + "' WHERE ( ID = " + CommandID.ToString() + " )";
					Update( Connection, CommandString );
				}

				Connection.Close();
			}

			Response.Redirect( "Default.aspx" );
		}
    }

    protected void BuilderDBRepeater_PromoteItemCommand_UE3( object source, RepeaterCommandEventArgs e )
    {
		BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedBuild", 1 );
    }

	protected void BuilderDBRepeater_PromoteItemCommand_UE4(object source, RepeaterCommandEventArgs e)
	{
		BuilderDBRepeater_PromoteItemCommand(e, "LatestApprovedBuild", 184 );
	}

	protected void BuilderDBRepeater_PromoteItemCommand_UE4Pretest( object source, RepeaterCommandEventArgs e )
	{
		BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedBuild", 198 );
	}

	protected void BuilderDBRepeater_PromoteItemCommand_ExodusE3( object source, RepeaterCommandEventArgs e )
	{
		BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedBuild", 193 );
	}

	protected void BuilderDBRepeater_PromoteItemCommand_Rift( object source, RepeaterCommandEventArgs e )
	{
		BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedBuild", 138 );
	}

	protected void BuilderDBRepeater_PromoteItemCommand_InfinityBlade1( object source, RepeaterCommandEventArgs e )
	{
		BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedBuild", 131 );
	}

	protected void BuilderDBRepeater_PromoteItemCommand_ProjectSword( object source, RepeaterCommandEventArgs e )
	{
		BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedBuild", 65 );
	}

	protected void BuilderDBRepeater_PromoteItemCommand_UE3_QA( object source, RepeaterCommandEventArgs e )
    {
        BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedQABuild", 1 );
    }

	protected void BuilderDBRepeater_PromoteItemCommand_UE4_QA( object source, RepeaterCommandEventArgs e )
	{
		BuilderDBRepeater_PromoteItemCommand( e, "LatestApprovedQABuild", 184 );
	}

    protected void Button_UE3QAChanges_Click( object sender, EventArgs e )
    {
        Button Pressed = ( Button )sender;
        if( Pressed.ID == "Button_UE3ChangesRange" )
        {
            string User = Context.User.Identity.Name;
            int Offset = User.LastIndexOf( '\\' );
            if( Offset >= 0 )
            {
                User = User.Substring( Offset + 1 );
            }

			using( SqlConnection Connection = new SqlConnection( ConfigurationManager.ConnectionStrings["BuilderConnectionString"].ConnectionString ) )
			{
				Connection.Open();
				string CommandString = "UPDATE Commands SET Pending = 1, Operator = '" + User + "' WHERE ( Description = '" + Pressed.Text + "' )";
				Update( Connection, CommandString );
				Connection.Close();
			}

            Response.Redirect( "Default.aspx" );
        }
    }

	protected void Button_UE4QAChanges_Click( object sender, EventArgs e )
	{
		Button Pressed = ( Button )sender;
		if( Pressed.ID == "Button_UE4ChangesRange" )
		{
			string User = Context.User.Identity.Name;
			int Offset = User.LastIndexOf( '\\' );
			if( Offset >= 0 )
			{
				User = User.Substring( Offset + 1 );
			}

			using( SqlConnection Connection = new SqlConnection( ConfigurationManager.ConnectionStrings["BuilderConnectionString"].ConnectionString ) )
			{
				Connection.Open();
				string CommandString = "UPDATE Commands SET Pending = 1, Operator = '" + User + "' WHERE ( Description = '" + Pressed.Text + "' )";
				Update( Connection, CommandString );
				Connection.Close();
			}

			Response.Redirect( "Default.aspx" );
		}
	}
}
