#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "company.h"


int main(){
    int option(-1), pipeID, CSID;
    std::vector<Pipe> myPipeline;
    std::vector<CompressorStation> myGasCompany;

    std::cout<<"Create your own gas producing company"<<std::endl;
    std::cout<<"#---------------------------------------------#"<<std::endl;

    while (option){
        std::cout<<"Choose menu's option:\n1.Add a pipe;\n2.Add a compressor station;\n3.Show all objects;\n4.Edit a pipe;\n5.Edit a compressor station;\n6.Save gas company;\n7.Load gas company;\n0.Close program"<<std::endl;
        option = checkInput(std::cin, INT_TYPE);
        if (option == -1)
            continue;
        if (option > 7){
            std::cout<<"Input error. Try again."<<std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            option = -1;
            system("pause");
            system("CLS");
            continue;
        }
        
// Checking option ------------------------------------------------------------------------------------------------------------------------

        if (option == 1){
    //Adding pipe ------------------------------------------------------------------
            std::cout<<"Input pipe\'s parameteres (length, diameter, status): ";
            double length = checkInput(std::cin, DOUBLE_TYPE);
            if (length == -1)
                continue;
            double diameter = checkInput(std::cin, DOUBLE_TYPE);
            if (diameter == -1)
                continue;
            int status = checkInput(std::cin, INT_TYPE);
            // std::cin>>length>>diameter>>status;
            if (status == -1)
                continue;

            pipeID = addPipe(myPipeline, length, diameter, status);

            std::cout<<"Id currently used pipe: "<<pipeID<<std::endl;
            std::cout<<std::endl;

        } else if (option == 2){
    //Adding compressor station ------------------------------------------------------
            int shopsAmount;
            std::vector<int> shops;
    
            std::cout<<"Input compressor station shops' amount: ";
            shopsAmount = checkInput(std::cin, INT_TYPE);
            if (shopsAmount == -1)
                continue;
            std::cout<<"Input compressor station each shop's status - \"1\" if it's \"in work\", and \"0\" if it is not (REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed): ";
            for (int i(0); i<shopsAmount; ++i){
                int status = checkInput(std::cin, INT_TYPE);
                status = (status > 1) ? 1 : status;
                if (status > -1)
                    shops.push_back(status);
                else if (status == -1){
                    i--;
                    continue;
                }else
                    shops.push_back(0);
            }

            CSID = addCompressorStation(myGasCompany, shopsAmount, shops);
            myGasCompany[CSID].efficiency = (double)std::count(shops.begin(), shops.end(), 1) / shopsAmount;

            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout<<"Id currently used compressor station: "<<CSID<<std::endl;
            std::cout<<std::endl; 

        } else if (option == 3){
    //Showing all existing objects -----------------------------------------------------
            showObjects(myPipeline, myGasCompany);

        } else if (option == 4){
    //Editing pipes -----------------------------------------------------------------------------------------------------------------------
            if (myPipeline.size() == 0){
                std::cout<<"Error: There're no pipes in your pipeline. Add one and try again."<<std::endl;
                system("pause");
                system("CLS");
                continue;
            }
            std::cout<<"Enter ID of the pipe you want to edit: "<<std::endl;
            pipeID = checkInput(std::cin, INT_TYPE);
            if (pipeID > myPipeline.size() - 1){
                std::cout<<"Error: There's no pipe with this ID in your pipeline. Try again."<<std::endl;
                system("pause");
                system("CLS");
                continue;
            }
            if (pipeID == -1){
                continue;
            }
            int suboption(-1);
            while (suboption){
                std::cout<<"Choose parameter you want to edit:\n1. Edit status;\n2. Edit length;\n3. Edit diameter;\n0. Quit editting mode"<<std::endl;
                suboption = checkInput(std::cin, INT_TYPE);
                if (suboption == -1)
                    continue;
                if (suboption > 3){
                    std::cout<<"Input error. Try again."<<std::endl;
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    suboption = -1;
                    system("pause");
                    continue;
                }
                editPipe(myPipeline[pipeID], suboption);
                system("pause");
                system("CLS");
            }
        } else if (option == 5){
            if (myGasCompany.size() == 0){
                std::cout<<"Error: There're no pipes in your pipeline. Add one and try again."<<std::endl;
                system("pause");
                system("CLS");
                continue;
            }
            std::cout<<"Enter ID of the compressor station you want to edit: "<<std::endl;
            CSID = checkInput(std::cin, INT_TYPE);
            std::cout<<"CSID: "<<CSID<<std::endl;
            if ((CSID > myGasCompany.size() - 1)){
                std::cout<<"Error: There's no pipe with this ID in your pipeline. Try again."<<std::endl;
                system("pause");
                system("CLS");
                continue;
            }
            if (CSID == -1)
                continue;
            
            int suboption(-1);
            while (suboption){
                std::cout<<"Choose parameter you want to edit:\n1. Edit shops amount;\n2. Edit shops statuses;\n0. Quit editting mode"<<std::endl;
                suboption = checkInput(std::cin, INT_TYPE);
                if (suboption == -1)
                    continue;
                if (suboption > 2){
                    std::cout<<"Input error. Try again."<<std::endl;
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    suboption = -1;
                    system("pause");
                    continue;
                }
                editCompressorStation(myGasCompany[CSID], suboption);
                system("pause");
                system("CLS");
            }
        } else if (option == 6){
            saveCompany(myPipeline, myGasCompany, "test.save");
        }

        system("pause");
        system("CLS");
    }
    return 0;
}
