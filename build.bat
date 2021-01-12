@echo off   
  
del .\Ylz.SqlViewer.zip
  
echo "building ...."  
  
"D:/Program Files (x86)/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin/MSBuild.exe" "Ylz.SqlViewer.sln" /t:Rebuild /p:Platform=x86 /p:Configuration=Release  

echo "creating zip package ...."

"D:\Program Files\7-Zip\7z.exe" a Ylz.SqlViewer.zip .\Release\*

echo "finished."
  
pause