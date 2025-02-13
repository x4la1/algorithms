SET MyProgram="%~1"
SET Out="%TEMP%\out.txt"


%MyProgram% input1.txt %Out% || goto err
fc %Out% output1.txt > nul|| goto err
echo 1 test passed

%MyProgram% input2.txt %Out% || goto err
fc %Out% output2.txt > nul|| goto err
echo 2 test passed

%MyProgram% input3.txt %Out% || goto err
fc %Out% output3.txt > nul|| goto err
echo 3 test passed

echo all tests passed
exit /B 0

:err
echo tests failed
exit /B 1
