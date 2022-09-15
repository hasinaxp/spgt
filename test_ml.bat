@echo off
cl /W3 /EHsc test_ml.cpp
test_ml.exe
del test_ml.obj
del test_ml.exe