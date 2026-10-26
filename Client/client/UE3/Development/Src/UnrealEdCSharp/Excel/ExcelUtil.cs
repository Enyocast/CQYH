using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Microsoft.Office.Interop.Excel;

namespace UnrealEdCSharp.Excel
{
    public class ExcelUtil
    {
//         struct HeaderInfo
//         {
//             int Index;
//             string Name;
//         };
        
//         bool FindHeaderIndex(out int outIdx, string header, string[] hdrList)
//         {
//             int colCnt = hdrList.GetLength(0);
//             for (int i = 0; i < colCnt; ++i)
//             {
//                 if (hdrList[i] == header)
//                 {
//                     outIdx = i;
//                     return true;
//                 }
//             }
// 
//             return false;
//         }

        public void SaveAsExcel(string[,] ItemList, String ExcelPath)
        {
            Microsoft.Office.Interop.Excel.Application app = new Microsoft.Office.Interop.Excel.Application();
#if !DEBUG
            try
            {
#endif
                app.Visible = false;
                string path = ExcelPath;// "D:\\test.xlsx";
                {
                    //Workbook book = app.Workbooks.Open(path);

                    Workbook book;
                    Sheets sheets;
                    Worksheet sheet;

                    if (System.IO.File.Exists(path))
                    {
                        book = app.Workbooks.Open(path, Type.Missing, false);
                        sheets = book.Worksheets;
                        sheet = (Worksheet)book.Sheets.get_Item(1);//["Sheet1"];
                    }
                    else
                    {
                        book = app.Workbooks.Add(true);

                        sheets = book.Worksheets;
                        sheet = (Worksheet)book.Sheets.get_Item(1);//["Sheet1"];
                    }

                    //DateTime start = DateTime.Now;

                    int rowCount = ItemList.GetLength(0);
                    int colCount = ItemList.GetLength(1);

                    //Range range = sheet.Cells[1, 1] as Range;
                    // range.get_Resize(rowCount, colCount);
                    
                    //先读表头，确定导出顺序
                    Range hdrRange = sheet.Cells.get_Range(sheet.Cells[1, 1], sheet.Cells[3, colCount]);
                    object[,] hdrArr = hdrRange.get_Value(Microsoft.Office.Interop.Excel.XlRangeValueDataType.xlRangeValueDefault) as object[,];

                    int hdrColCnt = hdrArr.GetLength(1);
                    string[] hdrList = new string[hdrColCnt];

                    List<string> hdrLst = new List<string>();

                    for (int c = 1; c <= hdrColCnt; ++c)
                    {
                        string str;
                        object obj = hdrArr[1, c];
                        if (obj == null)
                        {
                            str = "";
                        }
                        else
                        {
                            str = obj.ToString();
                        }

                        //hdrList[c] = str;
                        hdrLst.Add(str);
                    }

                    List<List<string>> strArr2D = new List<List<string>>();
                    for (int m = 0; m < rowCount; ++m )
                    {
                        List<string> tmpArr = new List<string>(colCount);
                        for (int n = 0; n < colCount; ++n )
                        {
                            tmpArr.Add("");
                        }
                        //tmpArr.Reverse(0, colCount);
                        strArr2D.Add(tmpArr);
                    }

                    List<int> addedCols = new List<int>();

                    int hdrCol = 0;
                    // 传入数据第一行是表头，第1列是索引
                    // 先对表头中有的放到数组中
                    int appendIdx = 0;
                    bool hasInvalidColumn = false;
                    for (hdrCol = 0; hdrCol < hdrLst.Count; ++hdrCol)
                    {
                        string hdrName = hdrLst[hdrCol];
                        if (hdrName == "")
                        {
                            continue;
                        }

                        ++appendIdx;
                        int idx = -1;
                        for (int findIdx = 0; findIdx < colCount; ++findIdx)
                        {
                            if (ItemList[0,findIdx] == hdrName)
                            {
                                idx = findIdx;
                                break;
                            }
                        }

                        if (idx != -1)
                        {
                            strArr2D[0][hdrCol] = hdrName; // header name
                            strArr2D[1][hdrCol] = ItemList[1, idx]; // client/server/both
                            object tmpVal = hdrArr[3, hdrCol + 1];
                            if(tmpVal != null)
                            {
                                strArr2D[2][hdrCol] = tmpVal.ToString(); // default value, 从EXCEL中出来的是1开始的下标
                            }

                            for (int r = 3; r < rowCount; ++r)
                            {
                                strArr2D[r][hdrCol] = ItemList[r,idx];
                            }

                            addedCols.Add(idx);
                        }
                        else
                        {
                            Range rangeC = sheet.Cells.get_Range(sheet.Cells[1, hdrCol + 1], sheet.Cells[1, hdrCol + 1]);
                            rangeC.Interior.ColorIndex = 3;

                            hasInvalidColumn = true;
                            strArr2D[0][hdrCol] = hdrName; // header name

                            object tmpVal = hdrArr[2, hdrCol];
                            if (tmpVal != null)
                            {
                                strArr2D[1][hdrCol] = tmpVal.ToString(); // client/server/both
                            }

                            tmpVal = hdrArr[3, hdrCol + 1];
                            if (tmpVal != null)
                            {
                                strArr2D[2][hdrCol] = tmpVal.ToString(); // default value, 从EXCEL中出来的是1开始的下标
                            }
                        }
                    }

                    if (hasInvalidColumn)
                    {
                        System.Windows.Forms.MessageBox.Show(string.Format(
                            "检查到有不用的列，表头已经标记为红色，请删除整列后再导出:{0}", ExcelPath));

                        app.Visible = true;
                        //book.Save();
                        //book.Saved = true;
                        //book.Close(false);
                        //app.Quit();
                        return;
                    }

                    // 再将新增加的添加到后面
                    for (hdrCol = 0; hdrCol < colCount; ++hdrCol)
                    {
                        if (-1 == addedCols.IndexOf(hdrCol))
                        {
                            for (int r = 0; r < rowCount; ++r)
                            {
                                strArr2D[r][appendIdx] = ItemList[r, hdrCol];
                            }

                            ++appendIdx;
                        }
                    }

                    string[,] destDat = new string[strArr2D.Count, colCount];
                    for (int k = 0; k < strArr2D.Count; ++k )
                    {
                        for (int l = 0; l < colCount; ++l )
                        {
                            destDat[k, l] = strArr2D[k][l];
                        }
                    }
#if DEBUG
                    for (int p = 0; p < strArr2D[0].Count; ++p )
                    {
                        string tmpStr = strArr2D[0][p];
                        if (tmpStr == "")
                        {
                            System.Diagnostics.Debug.Assert(false);
                        }
                    }
#endif
                    Range range = sheet.Cells.get_Range(sheet.Cells[1, 1], sheet.Cells[rowCount, colCount]);
                    range.set_Value(Microsoft.Office.Interop.Excel.XlRangeValueDataType.xlRangeValueDefault, destDat);


                    app.DisplayAlerts = false;
                    book.SaveAs(path);

                    int dotIdx = path.LastIndexOf(".");
                    string txtFile = path.Substring(0, dotIdx);
                    txtFile += ".txt";
                    book.SaveAs(txtFile, XlFileFormat.xlUnicodeText);
                    book.Saved = true;

//                     if (app.ThisWorkbook != null)
//                     {
//                         app.ThisWorkbook.Saved = true;
//                     }

                    book.Close(false);
                }
#if !DEBUG

            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.ToString());
            }
            finally
            {
#endif
                app.Quit();                
#if !DEBUG
            }
#endif
        }

        //从Excel中读取数据到一个列表中
        public void LoadFromExcel(String ExcelFile, out List<List<String>> outValues)
        {
            outValues = new List<List<string>>();
            //try
            {
                if (File.Exists(ExcelFile))
                {

                    Microsoft.Office.Interop.Excel.Application app = new Microsoft.Office.Interop.Excel.Application();
                    app.Visible = false;
                    Workbook book = app.Workbooks.Open(ExcelFile, Type.Missing, false);
                    Sheets sheets = book.Worksheets;
                    Worksheet sheet = (Worksheet)book.Sheets.get_Item(1);//["Sheet1"];
                    
                    Range usedRange = (Range)sheet.UsedRange;

                    Range range = sheet.Cells.get_Range(sheet.Cells[1, 1],
                        sheet.Cells[usedRange.Rows.Count, usedRange.Columns.Count]);

                    object[,] objArr = range.get_Value(Microsoft.Office.Interop.Excel.XlRangeValueDataType.xlRangeValueDefault) as object[,];

//                     if (app.ThisWorkbook != null)
//                     {
//                         app.ThisWorkbook.Saved = true;
//                     }

                    book.Close(false);
#if true
                    int rowCount = objArr.GetLength(0);
                    int colCount = objArr.GetLength(1);
                    for (int r = 1; r <= rowCount; ++r)
                    {
                        List<string> strLst = new List<string>();
                        for (int c = 1; c <= colCount; ++c)
                        {
                            string str;
                            object obj = objArr[r, c];
                            if (obj == null)
                            {
                                str = "";
                            }
                            else
                            {
                                str = obj.ToString();
                            }

                            strLst.Add(str);
                        }

                        outValues.Add(strLst);
                    }
#else
                    //string[,] arr = range.get_Value(Microsoft.Office.Interop.Excel.XlRangeValueDataType.xlRangeValueDefault) as string[,];

                    for (int i = 0; i < usedRange.Rows.Count; ++i)
                    {
                        Range row = (Range)usedRange.Rows[i + 1];
                        List<string> strLst = new List<string>();
                        for (int j = 0; j < row.Columns.Count; ++j)
                        {
                            Range Cell = (Range)usedRange.Cells[i + 1, j + 1];
                            if (Cell.Value != null)
                            {
                                strLst.Add(Cell.Value.ToString());
                            }
                            else
                            {
                                strLst.Add("0");
                            }
                        }
                        outValues.Add(strLst);
                    }
#endif
                    app.Quit();
                }
            }
            //             catch (System.Exception ex)
            //             {
            //                 System.Windows.Forms.MessageBox.Show(ex.ToString());
            //             }            
        }
    }
}
