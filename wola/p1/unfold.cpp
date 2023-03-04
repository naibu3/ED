#include <string>
#include <vector>
#include <iostream>
#include <sstream>      // std::istringstream
using namespace std;
int main(int argc,char*argv[]){
	try{
		vector<string> base={{" 1 2 3 ]"},{"[1]"},{"[1 ]"},{"[]"},{"[ ]"},{"[ 1]"},{"[ 1 2 3 4 5 ]"},{"[ 1 a 3]"}};
		if(argc==1){
			cout<<"[strings disponibles]"<<endl;
			for(int i=0;i<base.size();i++){
				cout<<"base"<<i<<": "<<base[i]<<endl;
			}
			cout<<"Elija uno mediante linea de comandos"<<endl;
			return 0;
		}
		string cadena=base[stoi(argv[1])];//el argv 1 elige la cadena a procesar
		std::stringstream in;
    	std::string token;
   		int num;
	    in<<cadena;
	    cout<<"la cadena que se va a evaluar es:\t"<<cadena<<endl<<endl;
	    //de aqui para abajo empieza el unfold (los cout simbolizan pushbacks)
	    in >> token;
	    if(token=="[]"){

	        cout<<"lista vacia"<<endl;
	        cout<<"la ejecucion del programa sale con normalidad"<<endl;
	    	return 0;
	    }

	    if(token!="["){
	    	cout<<endl<<"el primer elemento es distinto de [:\t"<<token<<endl;
	        throw std::runtime_error("Wrong input format.");
	    }
	    while(in>>token && token!="]"){
	        std::istringstream my_stream(token);
	        my_stream>>num;
	        if(my_stream.fail()){
	        	cout<<endl<<"lo que se ha introducido no era un numero:\t"<<token<<endl;
	            throw std::runtime_error("Wrong input format.");
	        }
	       cout<<num<<"<";
	    }
	    if(token != "]"){
	    	cout<<endl<<"El ultimo elemento no era ]\t"<<token<<endl;
	        throw std::runtime_error("Wrong input format.");
	    }
	    cout<<"la ejecucion del programa sale con normalidad"<<endl;
	}
	catch(std::runtime_error &e){
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

}
