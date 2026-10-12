// ----------------------------------------------------------------------------
// Example Scrip + Input Simulate
// ----------------------------------------------------------------------------


function main()
{

  var scriptlog;
  var scriptname;
  var appname         = "wordpad.exe";
  var apppath         = "C:\\Program Files (x86)\\Windows NT\\Accessories\\" + appname;
  var windowtitle     = "WordPad";
  var maskbitmapname  = "inputsimul.png"

  scriptlog   = GetPathScript() +  GetNameScript() + ".log";
  scriptname  = GetNameScript() + ".js";

  
  if(!Log_Ini(scriptlog, "ScriptsExample"))
    {
      return;  
    }
  
  Log_CFG_SetLimit(30000, 3);
  Log_CFG_SetFilters("Script", 0x000F);
  Log_CFG_SetBackup(true, 10, true);     
  
 
  TraceClearScreen(true);
  TraceClearMsgsStatus(true);

  Log_AddEntry(1, "Script", "[script %s] Iniciado Test...", scriptname);

  ExecApplication(apppath);

  Log_AddEntry(1, "Script", "[script %s] Exec application: %s", scriptname, appname);
 
  Window_SetPosition(appname, windowtitle, 10, 10);
  Window_Resize(appname, windowtitle, 800, 600);
  Window_SetFocus(appname, windowtitle);

  Window_SetBmpFindCFG(2, 0);

  var posx = Window_GetPosX(appname, windowtitle, maskbitmapname);
  var posy = Window_GetPosY(appname, windowtitle, maskbitmapname);

  TracePrintColor(1, "Position of %s %d, %d", appname, posx, posy);

  InpSim_Mouse_Click(posx, posy);

  /*
  InpSim_Mouse_Click(posx + 30, posy + 50);

  Sleep(1000);

  InpSim_Mouse_Click(posx + 30, posy + 50);

  Sleep(1000);
  

  InpSim_Mouse_Click(posx + 80, posy + 450);

  Sleep(1000);

  InpSim_Key_ClickByLiteral("A", 100);
  InpSim_Key_ClickByLiteral("ENTER", 100);

  Log_AddEntry(1, "Script", "[script %s] Simulate Key A + Enter.", scriptname)
  
  InpSim_Key_ClickByLiteral("!"  , 1);
  InpSim_Key_ClickByLiteral("@"  , 1);
  InpSim_Key_ClickByLiteral("#"  , 1);
  InpSim_Key_ClickByLiteral("$"  , 1);
  InpSim_Key_ClickByLiteral("%"  , 1);
  InpSim_Key_ClickByLiteral("^"  , 1);
  InpSim_Key_ClickByLiteral("&"  , 1);
  InpSim_Key_ClickByLiteral("*"  , 1);
  InpSim_Key_ClickByLiteral("("  , 1);
  InpSim_Key_ClickByLiteral(")"  , 1);
  InpSim_Key_ClickByLiteral("_"  , 1);
  InpSim_Key_ClickByLiteral("+"  , 1);
  InpSim_Key_ClickByLiteral("-"  , 1);
  InpSim_Key_ClickByLiteral("="  , 1);
  InpSim_Key_ClickByLiteral("["  , 1);
  InpSim_Key_ClickByLiteral("]"  , 1);
  InpSim_Key_ClickByLiteral("{"  , 1);
  InpSim_Key_ClickByLiteral("}"  , 1);
  InpSim_Key_ClickByLiteral("|"  , 1);
  InpSim_Key_ClickByLiteral(";"  , 1);
  InpSim_Key_ClickByLiteral(":"  , 1);
  InpSim_Key_ClickByLiteral("'"  , 1);
  InpSim_Key_ClickByLiteral(","  , 1);
  InpSim_Key_ClickByLiteral("."  , 1);
  InpSim_Key_ClickByLiteral("<"  , 1);   
  InpSim_Key_ClickByLiteral("?"  , 1);
  InpSim_Key_ClickByLiteral("/"  , 1);
  InpSim_Key_ClickByLiteral("\\" , 1);
  InpSim_Key_ClickByLiteral("\"" , 1);
  
  //InpSim_Key_ClickByLiteral("¿"  , 1);
  //InpSim_Key_ClickByLiteral("¡"  , 1);
  //InpSim_Key_ClickByLiteral("ñ"  , 1);
  //InpSim_Key_ClickByLiteral("Ñ"  , 1);
  //InpSim_Key_ClickByLiteral("·"  , 1);
 
  InpSim_Key_ClickByLiteral("ENTER", 1);

  InpSim_Key_ClickByText("Texto De Prueba 0123456789 !@#$%^&*()_+-=[]{}|;:',.<¿¡ñÑ?/\\\"·", 1);
  */

  Sleep(1000);

  Log_AddEntry(1, "Script", "[script %s] Terminate application: %s", scriptname, appname);

  TerminateAplicationWithWindow(appname, windowtitle);  

  Log_AddEntry(1, "Script", "[script %s] End script.", scriptname);
  
}

