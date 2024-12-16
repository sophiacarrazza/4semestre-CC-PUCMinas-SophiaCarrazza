#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    cout << "Iniciando" << endl;
    

    try
    {
        system("g++ -o seedMark seedMark.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc `pkg-config --cflags --libs opencv4`");
        system("./seedMark");
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "verifique as dependencias para rodas as bibliotecas nescessarias";
    }//g++ -o a 2artigo.cpp graph.cpp maxflow.cpp
    

    std::cout << "Pressione Enter para continuar...";
    std::cin.get(); 
    system("g++ -o 2artigo 2artigo.cpp graph.cpp maxflow.cpp");
    system("./2artigo");

    return 0;
}
