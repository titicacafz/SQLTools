@echo off  
  
call "D:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"  
  
echo "building ...."  
  
MSBuild "Ylz.SqlViewer.sln" /t:Rebuild /p:Platform=x86 /p:Configuration=Release  
  
pause