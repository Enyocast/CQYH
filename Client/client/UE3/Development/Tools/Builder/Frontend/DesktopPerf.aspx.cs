/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class DesktopPerf : System.Web.UI.Page
{
	private void FillSeries( SqlConnection Connection, string Item, int CounterID, int MachineID )
	{
		using( SqlCommand Command = new SqlCommand( "SELECT Changelist, IntValue / 1000 AS " + Item + ", DateTimeStamp FROM PerformanceData " +
													"WHERE ( CounterID = " + CounterID.ToString() + " ) AND ( MachineID = " + MachineID.ToString() + " ) AND ( DATEDIFF( day, '8/31/2012', DateTimeStamp ) >= 0 ) " +
													"ORDER BY Changelist", Connection ) )
		{
			SqlDataReader Reader = Command.ExecuteReader();
			if( Reader.HasRows )
			{
				DataTable Table = new DataTable();
				Table.Load( Reader );

				DesktopPerfChart.Series[Item].Points.DataBindXY( Table.Rows, "Changelist", Table.Rows, Item );
			}

			Reader.Close();
		}
	}

	protected void Page_Load( object sender, EventArgs e )
	{
		using( SqlConnection Connection = new SqlConnection( ConfigurationManager.ConnectionStrings["BuilderConnectionString"].ConnectionString ) )
		{
			Connection.Open();
			FillSeries( Connection, "UCSUDK", 1438, 93 );
			FillSeries( Connection, "UCSExample", 1437, 93 );
			FillSeries( Connection, "UCSFortnite", 1485, 93 );
			FillSeries( Connection, "T7600UDK", 1438, 120 );
			FillSeries( Connection, "T7600Example", 1437, 120 );
			FillSeries( Connection, "T7600Fortnite", 1485, 120 );
			FillSeries( Connection, "D30UDK", 1438, 121 );
			FillSeries( Connection, "D30Example", 1437, 121 );
			FillSeries( Connection, "D30Fortnite", 1485, 121 );
			Connection.Close();
		}
	}
}