@echo off   
  
del .\Ylz.SqlViewer.zip  
  
call "D:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\Common7\Tools\VsDevCmd.bat"  
  
echo "building ...."  
  
MSBuild "Ylz.SqlViewer.sln" /t:Rebuild /p:Platform=x86 /p:Configuration=Release  

echo "creating zip package ...."

"D:\Program Files\7-Zip\7z.exe" a Ylz.SqlViewer.zip .\Release\*

echo "finished."
  
pause