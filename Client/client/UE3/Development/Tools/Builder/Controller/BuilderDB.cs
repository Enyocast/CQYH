/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */

using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Text;
using System.Threading;

using Controller.Models;

namespace Controller
{
    public partial class BuilderDB
    {
        private Main Parent = null;
        private SqlConnection Connection = null;
		private bool SendWarningEmailsOnDBErrors = false;
		private bool RetryAllConnections = true;
		private int RetrySleepTimeInMS = 5 * 1000;
		private int MaxRetryCount = 3;

        public BuilderDB( Main InParent )
        {
			Parent = InParent;

			if( !OpenConnection() )
			{
				// If opening the connection fails, stop the whole show
				Parent.Ticking = false;
			}
        }

		public bool OpenConnection()
		{
			try
			{
				Connection = new SqlConnection( Properties.Settings.Default.DBConnection );
				Connection.Open();

				Parent.Log( "Database connection opened successfully", Color.DarkGreen );
				return true;
			}
			catch( Exception Ex )
			{
				Parent.Log( "Database open exception: " + Ex.ToString(), Color.Red );
				Connection = null;
				return false;
			}
		}

		public void CloseConnection()
		{
			if( Connection != null )
			{
				try
				{
					Connection.Close();
					Parent.Log( "Database connection closed successfully", Color.DarkGreen );
				}
				catch( System.Exception Ex )
				{
					Parent.Log( "Database close exception: " + Ex.ToString(), Color.Red );
				}

				Connection = null;
			}
		}

		public void Update( string CommandString )
		{
			bool TransactionCompleted = false;
			int RetryCount = 0;
			while( !TransactionCompleted )
			{
				try
				{
					SqlCommand Command = new SqlCommand( CommandString, Connection );
					Command.ExecuteNonQuery();
					TransactionCompleted = true;
				}
				catch( Exception Ex )
				{
					Parent.Log( "BuilderDB.Update exception: " + Ex.ToString(), Color.Red );
					Parent.Log( "Query: " + CommandString, Color.Red );

					// If we're retrying, sleep for a bit and loop
					if( RetryAllConnections && ( RetryCount < MaxRetryCount ) )
					{
						if( SendWarningEmailsOnDBErrors )
						{
							Parent.SendWarningMail( "Database exception, retrying", Ex.ToString(), false );
						}

						CloseConnection();

						do
						{
							System.Threading.Thread.Sleep( RetrySleepTimeInMS );
							RetryCount++;
						}
						while( !OpenConnection() && ( RetryCount < MaxRetryCount ) );
					}
					else
					{
						TransactionCompleted = true;
						if( SendWarningEmailsOnDBErrors )
						{
							Parent.SendWarningMail( "BuilderDB.Update exception", "Query: " + CommandString + "\nException: " + Ex.ToString(), false );
						}
					}
				}
			}
		}

		private SqlDataReader ExecuteQuery( string Description, string Query, SqlConnection Connection )
		{
			SqlDataReader DataReader = null;
			bool TransactionCompleted = false;
			int RetryCount = 0;
			while( !TransactionCompleted )
			{
				try
				{
					SqlCommand Command = new SqlCommand( Query, Connection );
					DataReader = Command.ExecuteReader();
					TransactionCompleted = true;
				}
				catch( Exception Ex )
				{
					Parent.Log( Description + " exception: " + Ex.ToString(), Color.Red );
					Parent.Log( "Query: " + Query, Color.Red );

					// If we're retrying, sleep for a bit and loop
					if( RetryAllConnections && ( RetryCount < MaxRetryCount ) )
					{
						if( SendWarningEmailsOnDBErrors )
						{
							Parent.SendWarningMail( "Database exception, retrying", Ex.ToString(), false );
						}

						CloseConnection();

						do
						{
							System.Threading.Thread.Sleep( RetrySleepTimeInMS );
							RetryCount++;
						}
						while( !OpenConnection() && ( RetryCount < MaxRetryCount ) );
					}
					else
					{
						TransactionCompleted = true;
					}
				}
			}

			return ( DataReader );
		}

		public int ReadInt( string CommandString )
		{
			int Result = 0;
			SqlDataReader DataReader = ExecuteQuery( "BuilderDB.ReadInt", CommandString, Connection );

			if( DataReader != null )
			{
				try
				{
					if( DataReader.Read() && !DataReader.IsDBNull( 0 ) )
					{
						Result = DataReader.GetInt32( 0 );
					}
				}
				catch( System.Exception Ex )
				{
					Parent.Log( "BuilderDB.ReadInt(" + CommandString + ") exception: " + Ex.ToString(), Color.Red );
				}

				DataReader.Close();
			}

			return ( Result );
		}

		public double ReadDouble( string CommandString )
		{
			double Result = 0;

			SqlDataReader DataReader = ExecuteQuery( "BuilderDB.ReadDouble", CommandString, Connection );

			if( DataReader != null )
			{
				try
				{
					if( DataReader.Read() && !DataReader.IsDBNull( 0 ) )
					{
						Result = ( double )DataReader.GetDecimal( 0 );
					}
				}
				catch( System.Exception Ex )
				{
					Parent.Log( "BuilderDB.ReadDouble(" + CommandString + ") exception: " + Ex.ToString(), Color.Red );
				}

				DataReader.Close();
			}

			return ( Result );
		}

		public bool ReadBool( string CommandString )
		{
			bool Result = false;

			SqlDataReader DataReader = ExecuteQuery( "BuilderDB.ReadBool", CommandString, Connection );

			if( DataReader != null )
			{
				try
				{
					if( DataReader.Read() && !DataReader.IsDBNull( 0 ) )
					{
						Result = DataReader.GetBoolean( 0 );
					}
				}
				catch( System.Exception Ex )
				{
					Parent.Log( "BuilderDB.ReadBool(" + CommandString + ") exception: " + Ex.ToString(), Color.Red );
				}

				DataReader.Close();
			}

			return ( Result );
		}

		public string ReadString( string CommandString )
		{
			string Result = "";

			SqlDataReader DataReader = ExecuteQuery( "BuilderDB.ReadString", CommandString, Connection );

			if( DataReader != null )
			{
				try
				{
					if( DataReader.Read() && !DataReader.IsDBNull( 0 ) )
					{
						Result = DataReader.GetString( 0 );
					}
				}
				catch( System.Exception Ex )
				{
					Parent.Log( "BuilderDB.ReadString(" + CommandString + ") exception: " + Ex.ToString(), Color.Red );
				}

				DataReader.Close();
			}

			return ( Result );
		}

		public DateTime ReadDateTime( string CommandString )
		{
			DateTime Result = DateTime.UtcNow;

			SqlDataReader DataReader = ExecuteQuery( "BuilderDB.ReadDateTime", CommandString, Connection );

			if( DataReader != null )
			{
				try
				{
					if( DataReader.Read() && !DataReader.IsDBNull( 0 ) )
					{
						Result = DataReader.GetDateTime( 0 );
					}
				}
				catch( System.Exception Ex )
				{
					Parent.Log( "BuilderDB.ReadDateTime(" + CommandString + ") exception: " + Ex.ToString(), Color.Red );
				}

				DataReader.Close();
			}

			return ( Result );
		}

		public void FindSuppressedJobs( ScriptParser Builder, long JobSpawnTime )
		{
			List<Main.SuppressedJobsInfo> SuppressedJobs = BuilderLinq.FindSuppressedJobs( JobSpawnTime );

			foreach( Main.SuppressedJobsInfo SuppressedJob in SuppressedJobs )
			{
				GameConfig GameInfo = new GameConfig( SuppressedJob.Game, SuppressedJob.Platform, SuppressedJob.Config, null, true, true );
				Builder.LabelInfo.FailedGames.Add( GameInfo );
			}
		}

        public string GetVariable( string Branch, string Var )
        {
            string Query = "SELECT Value FROM Variables WHERE ( Variable = '" + Var + "' AND Branch = '" + Branch + "' )";
            string Result = ReadString( Query );
            return ( Result );
        }

        public void SetLastAttemptedBuild( int CommandID, int ChangeList, DateTime Time )
        {
            if( CommandID != 0 )
            {
                if( ChangeList != 0 )
                {
                    SetInt( "Commands", CommandID, "LastAttemptedChangeList", ChangeList );
                }

                SetDateTime( "Commands", CommandID, "LastAttemptedDateTime", Time );
            }
        }

        public void SetLastFailedBuild( int CommandID, int ChangeList, DateTime Time )
        {
            if( CommandID != 0 )
            {
                if( ChangeList != 0 )
                {
                    SetInt( "Commands", CommandID, "LastFailedChangeList", ChangeList );
                }

                SetDateTime( "Commands", CommandID, "LastFailedDateTime", Time );
            }
        }

        public void SetLastGoodBuild( int CommandID, int ChangeList, DateTime Time )
        {
            if( CommandID != 0 )
            {
                SetInt( "Commands", CommandID, "LastGoodChangeList", ChangeList );
                SetDateTime( "Commands", CommandID, "LastGoodDateTime", Time );
            }
        }

        public void Trigger( int CurrentCommandID, string BuildDescription, bool bForceAutoTimerUser )
        {
            string Query = "SELECT ID FROM Commands WHERE ( Description = '" + BuildDescription + "' )";
            int CommandID = ReadInt( Query );

			if( CommandID != 0 )
			{
				Query = "SELECT Machine FROM Commands WHERE ( ID = " + CommandID.ToString() + " )";
				string Machine = ReadString( Query );

				if( Machine.Length == 0 )
				{
					string User = "AutoTimer";
					if( !bForceAutoTimerUser )
					{
						Query = "SELECT Operator FROM Commands WHERE ( ID = " + CurrentCommandID.ToString() + " )";
						User = ReadString( Query );
					}

					Query = "UPDATE Commands SET Pending = '1', Operator = '" + User + "' WHERE ( ID = " + CommandID.ToString() + " )";
					Update( Query );
				}
				else
				{
					Parent.Log( " ... suppressing retrigger of '" + BuildDescription + "'", Color.Magenta );
					string Operator = GetString( "Commands", CommandID, "Operator" );
					Parent.SendAlreadyInProgressMail( Operator, CommandID, BuildDescription );
				}
			}
			else
			{
				Parent.SendErrorMail( "Build '" + BuildDescription + "' does not exist!", "" );
			}
        }

        public void Trigger( int CommandID )
        {
            string Query = "SELECT Operator FROM Commands WHERE ( ID = " + CommandID.ToString() + " )";
            string User = ReadString( Query );

            Query = "UPDATE Commands SET Pending = '1', Operator = '" + User + "' WHERE ( ID = " + CommandID.ToString() + " )";
            Update( Query );
        }

        public int PollForKillBuild()
        {
            string QueryString = "SELECT ID FROM Commands WHERE ( Machine = '" + Parent.MachineName + "' AND Killing = 1 )";
            int ID = ReadInt( QueryString );
            return ( ID );
        }

        public int PollForKillJob()
        {
            string QueryString = "SELECT ID FROM Jobs WHERE ( Machine = '" + Parent.MachineName + "' AND Killing = 1 AND Complete = 0 )";
            int ID = ReadInt( QueryString );
            return ( ID );
        }

        public int PollForBuild( string MachineName, bool bPrimaryBuildsOnly )
        {
            int ID;

            // Check for machine locked timed build
			ID = BuilderLinq.CheckTimedBuild( MachineName, false, bPrimaryBuildsOnly );
            if( ID >= 0 )
            {
                // Check for success
                if( ID != 0 )
                {
                    SetString( "Commands", ID, "Operator", "AutoTimer" );
                    return ( ID );
                }

                // Check for a machine locked triggered build
				ID = BuilderLinq.CheckTriggeredBuild( MachineName, false, bPrimaryBuildsOnly );
                if( ID >= 0 )
                {
                    // Check for success
                    if( ID != 0 )
                    {
                        return ( ID );
                    }

                    // If this machine locked to a build then don't allow it to grab normal ones
                    if( Parent.MachineLock != 0 )
                    {
                        return ( 0 );
                    }

                    // Poll for a timed build to be grabbed by anyone
					ID = BuilderLinq.CheckTimedBuild( MachineName, true, bPrimaryBuildsOnly );
					if( ID >= 0 )
                    {
                        // Check for success
                        if( ID != 0 )
                        {
                            SetString( "Commands", ID, "Operator", "AutoTimer" );
                            return ( ID );
                        }

                        // Poll for a triggered build
						ID = BuilderLinq.CheckTriggeredBuild( MachineName, true, bPrimaryBuildsOnly );
                    }
                }
            }
            return ( ID );
        }

		public void KillAssociatedJobs( string LabelName )
		{
			string Query = "UPDATE Jobs SET Killing = 1 WHERE ( Label = '" + LabelName + "' )";
			Update( Query );
		}

        public int GetInt( string TableName, int ID, string Command )
        {
            int Result = 0;

            if( ID != 0 )
            {
                string Query = "SELECT " + Command + " FROM " + TableName + " WHERE ( ID = " + ID.ToString() + " )";
                Result = ReadInt( Query );
            }

            return ( Result );
        }

        public bool GetBool( string TableName, int ID, string Command )
        {
            bool Result = false;

            if( ID != 0 )
            {
                string Query = "SELECT " + Command + " FROM " + TableName + " WHERE ( ID = " + ID.ToString() + " )";
                Result = ReadBool( Query );
            }

            return ( Result );
        }

        public string GetString( string TableName, int ID, string Command )
        {
            string Result = "";

            if( ID != 0 )
            {
                string Query = "SELECT " + Command + " FROM " + TableName + " WHERE ( ID = " + ID.ToString() + " )";
                Result = ReadString( Query );
            }

            return ( Result );
        }

		public string GetStringForBranch( string Branch, string Command )
		{
			string Query = "SELECT " + Command + " FROM BranchConfig WHERE ( Branch = '" + Branch + "' )";
			string Result = ReadString( Query );

			return ( Result );
		}

		public int GetIntForBranch( string Branch, string Command )
		{
			string Query = "SELECT " + Command + " FROM BranchConfig WHERE ( Branch = '" + Branch + "' )";
			int Result = ReadInt( Query );

			return ( Result );
		}

		public string GetStringForServer( string Server, string Command )
		{
			string Query = "SELECT " + Command + " FROM BranchConfig WHERE ( Server = '" + Server + "' )";
			string Result = ReadString( Query );

			return ( Result );
		}

        public DateTime GetDateTime( string TableName, int ID, string Command )
        {
            DateTime Result = DateTime.UtcNow;

            if( ID != 0 )
            {
                string Query = "SELECT " + Command + " FROM " + TableName + " WHERE ( ID = " + ID.ToString() + " )";
                Result = ReadDateTime( Query );
            }

            return ( Result );
        }

        public void SetString( string TableName, int ID, string Field, string Info )
        {
            if( ID != 0 )
            {
                Info = Info.Replace( "'", "" );

                string Command = "UPDATE " + TableName + " SET " + Field + " = '" + Info + "' WHERE ( ID = " + ID.ToString() + " )";
                Update( Command );
            }
        }

        public void SetInt( string TableName, int ID, string Field, int Info )
        {
            if( ID != 0 )
            {
                string Command = "UPDATE " + TableName + " SET " + Field + " = " + Info.ToString() + " WHERE ( ID = " + ID.ToString() + " )";
                Update( Command );
            }
        }

		public void SetIntForBranch( string Branch, string Field, int Changelist )
		{
			string Command = "Update BranchConfig SET " + Field + " = " + Changelist.ToString() + " WHERE ( Branch = '" + Branch + "' )";
			Update( Command );
		}

        public void SetBool( string TableName, int ID, string Field, bool BoolInfo )
        {
            if( ID != 0 )
            {
                int Info = 0;
                if( BoolInfo )
                {
                    Info = 1;
                }
                string Command = "UPDATE " + TableName + " SET " + Field + " = " + Info.ToString() + " WHERE ( ID = " + ID.ToString() + " )";
                Update( Command );
            }
        }

        public void SetDateTime( string TableName, int ID, string Field, DateTime Time )
        {
            if( ID != 0 )
            {
                string Command = "UPDATE " + TableName + " SET " + Field + " = '" + Time.ToString( Main.US_TIME_DATE_STRING_FORMAT ) + "' WHERE ( ID = " + ID.ToString() + " )";
                Update( Command );
            }
        }

        public void Delete( string TableName, int ID, string Field )
        {
            if( ID != 0 )
            {
                string Command = "UPDATE " + TableName + " SET " + Field + " = null WHERE ( ID = " + ID.ToString() + " )";
                Update( Command );
            }
        }
    }
}
