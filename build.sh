g++ main.cpp `wx-config --cxxflags --libs` -o app.exe
if [ $? -eq 0 ]; then
    ./app.exe
fi