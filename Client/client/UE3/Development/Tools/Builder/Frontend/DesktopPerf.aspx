<%@ Page Language="C#" AutoEventWireup="true" CodeFile="DesktopPerf.aspx.cs" Inherits="DesktopPerf" %>

<%@ Register assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35" namespace="System.Web.UI.DataVisualization.Charting" tagprefix="asp" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title></title>
</head>
<body>
<center>
    <form id="form1" runat="server">
    <asp:Label ID="Label_Title" runat="server" Font-Bold="True" Font-Names="Arial" Font-Size="X-Large" ForeColor="Blue" Height="48px" Text="Comparative Desktop Performance" Width="640px"></asp:Label>
<br />
    <div>
    
        <asp:Chart ID="DesktopPerfChart" runat="server" Height="1000px" Width="1500px">
            <Legends>
                <asp:Legend Name="Legend1" Alignment="Center" Docking="Bottom">
                </asp:Legend>
            </Legends>
            <series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="UCSExample" BorderWidth="2" Color="Lime"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="UCSUDK" BorderWidth="2" Color="Green"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="UCSFortnite" BorderWidth="2" Color="DarkGreen"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="T7600Example" BorderWidth="2" Color="Red"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="T7600UDK" BorderWidth="2" Color="Crimson"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="T7600Fortnite" BorderWidth="2" Color="DarkRed"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="D30Example" BorderWidth="2" Color="Blue"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="D30UDK" BorderWidth="2" Color="Cyan"></asp:Series>
                <asp:Series ChartArea="ChartArea1" ChartType="Line" Legend="Legend1" Name="D30Fortnite" BorderWidth="2" Color="DarkBlue"></asp:Series>
			</series>
            <chartareas>
                <asp:ChartArea Name="ChartArea1">
                    <AxisX Interval="5000">
                    </AxisX>
                </asp:ChartArea>
            </chartareas>
        </asp:Chart>
    
    </div>
    </form>
    </center>
</body>
</html>

