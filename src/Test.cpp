#include <iostream>

#include "Company.h"

using namespace std;

/*void thisIsATest() {
 ASSERTM("start writing tests", false);
 }*/

/*void runAllTests(int argc, char const *argv[]){
 cute::suite s;
 //TODO add your test here
 s.push_back(CUTE(thisIsATest));
 cute::xml_file_opener xmlfile(argc,argv);
 cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
 cute::makeRunner(lis,argc,argv)(s, "AllTests");
 }*/

void gestaoEcoPontos(Company& emp) {
	while (1) {
		system("cls");
		cout << "1. Ver EcoPontos;" << endl;
		cout << "2. Criar EcoPontos aleatorios;" << endl;
		cout << "3. Adicionar EcoPonto;" << endl;
		cout << "4. Remover EcoPonto;" << endl;
		cout << "5. Apagar EcoPontos;" << endl;
		cout << "6. Adicionar lixo aleatorio;" << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1':
			system("cls");
			cout << emp.getSBins() << endl;
			getch();
			break;
		case '2': {
			system("cls");
			int c = emp.createRandomReBins();
			cout << "Criou " << c << " ecopontos!" << endl;
			getch();
			break;
		}
		case '3': {
			system("cls");
			cout << "Id do vertex: ";
			int idv;
			cin >> idv;
			if (emp.createReBins(idv)) {
				cout << "Ecoponto criado!" << endl;
			} else {
				cout << "Vertex inexistente! Ecoponto nao criado!" << endl;
			}
			getch();
			break;
		}
		case '4': {
			system("cls");
			cout << "ID do ecoponto: ";
			int id;
			cin >> id;
			if (emp.removeReBin(id)) {
				cout << "Ecoponto removido!" << endl;
			} else {
				cout << "Ecoponto inexistente!" << endl;
			}
			break;
		}
		case '5':
			system("cls");
			cout << "Eliminou " << emp.eraseReBins() << " ecopontos!" << endl;
			getch();
			break;
		case '6':
			system("cls");
			emp.generateGarbage();
			cout << "Lixo criado!" << endl;
			getch();
			break;
		case '9':
			return;
		default:
			break;
		}
	}
}

void gestaoCamioes(Company& emp) {
	while (1) {
		system("cls");
		cout << "1. Ver camioes;" << endl;
		cout << "2. Criar camioes aleatorios;" << endl;
		cout << "3. Adicionar camiao;" << endl;
		cout << "4. Remover camiao;" << endl;
		cout << "5. Apagar camioes;" << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1':
			system("cls");
			cout << emp.getSTrucks() << endl;
			getch();
			break;
		case '2':
			system("cls");
			cout << "Criou " << emp.createTrucks() << " camioes!" << endl;
			getch();
			break;
		case '3':
			system("cls");

			getch();
			break;
		case '4':
			system("cls");

			getch();
			break;
		case '5':
			system("cls");
			cout << "Eliminou " << emp.eraseTrucks() << " camioes!" << endl;
			getch();
			break;
		case '9':
			return;
		default:
			break;
		}
	}
}

void gestaoEcoCentros(Company& emp) {
	while (1) {
		system("cls");
		cout << "1. Ver EcoCentros;" << endl;
		cout << "2. Criar EcoCentros aleatorios;" << endl;
		cout << "3. Adicionar EcoCentro;" << endl;
		cout << "4. Remover EcoCentro;" << endl;
		cout << "5. Apagar EcoCentros;" << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1':
			system("cls");
			cout << emp.getSCenters() << endl;
			getch();
			break;
		case '2':
			system("cls");
			cout << "Nao implementado!" << endl;
			getch();
			break;
		case '3':
			system("cls");
			cout << "Vertex id: " << endl;
			int idv;
			cin >> idv;
			if (emp.createReCenter(idv)) {
				cout << "Ecocentro criado!" << endl;
			} else {
				cout << "Vertex inexistente! Ecocentro nao criado!" << endl;
			}
			getch();
			break;
		case '4':
			system("cls");
			cout << "Nao implementado!" << endl;
			getch();
			break;
		case '5':
			system("cls");
			cout << "Eliminou " << emp.eraseReCenters() << " ecocentros!"
					<< endl;
			getch();
			break;
		case '9':
			return;
		default:
			break;
		}
	}
}

void gestao(Company& emp) {
	while (1) {
		system("cls");
		cout << "1. Gerir EcoPontos;" << endl;
		cout << "2. Gerir Camioes;" << endl;
		cout << "3. Gerir EcoCentros;" << endl;
		cout << "4. " << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1':
			gestaoEcoPontos(emp);
			break;
		case '2':
			gestaoCamioes(emp);
			break;
		case '3':
			gestaoEcoCentros(emp);
			break;
		case '4':
			system("cls");
			emp.dynamic();
			getch();
			break;
		case '9':
			return;
		default:
			break;
		}
	}
}

void rotas(Company& emp) {
	while (1) {
		system("cls");
		cout << "1. Rota com capacidade ilimitada;" << endl;
		cout << "2. Rota com capacidade limitada;" << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1': {
			system("cls");
			int idp, idc;
			cout << "Id do ecocentro de partida: ";
			cin >> idp;
			cout << "Id do ecocentro de chegada: ";
			cin >> idc;
			cout << emp.getUnlimitedRun(idp, idc);
			getch();
			break;
		}
		case '2': {
			system("cls");
			int idp, idc;
			cout << "Id do ecocentro de partida: ";
			cin >> idp;
			cout << "Id do ecocentro de chegada: ";
			cin >> idc;
			cout << emp.getLimitedRun(idp, idc);
			getch();
			break;
		}
		case '9':
			return;
		default:
			break;
		}
	}
}

int menu() {
	Company emp = Company();
	while (1) {
		system("cls");
		cout << "1. Gestao de dados;" << endl;
		cout << "2. Calculo de rotas;" << endl; //CAROLINA HELP ME PLIZ
		cout << "3. Informacao para recolha;" << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1':
			gestao(emp);
			break;
		case '2':
			rotas(emp);
			break;
		case '3': {
			system("cls");
			emp.dynamic();
			getch();
		}
			break;
		case '4':
			break;
		case '9':
			return 0;
		default:
			break;
		}
	}
	return 1;
}

int main() {
	//   runAllTests(argc,argv);
	return menu();
}
