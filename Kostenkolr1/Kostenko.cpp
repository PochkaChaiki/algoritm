#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <bits/stdc++.h>
#include "GasCompany.h"
#include "utils.h"

int main(){
    int option(-1), pipeID, CSID;

    GasCompany myCompany;
    std::cout<<"#---------------------------------------------#"<<std::endl;
    std::cout<<"Create your own gas producing company"<<std::endl;

    while (option){
        std::cout << "#----------------------------------------------#" << std::endl;
        std::cout << "Choose menu's option:\n1.Add a compressor station;\n2.Connect compressor stations with pipe;\n3.Show all objects;\n4.Edit a pipe;"
                  << "\n5.Edit a compressor station;\n6.Save gas company;\n7.Load gas company;\n8.Find specific objects;\n9.Unlink(don't work for now);\n10.Topological Sort;\n0.Close program" << std::endl;

        option = GetRightValue(std::cin, 0, 10);
        
// Checking option ------------------------------------------------------------------------------------------------------------------------
        if (option == 1){
    // Adding compressor station --------------------------------------------------------
            myCompany.addCS();

        } else if (option == 2){
    // Adding pipe ----------------------------------------------------------------------
            myCompany.addConnection();

        } else if (option == 3){
    // Showing all existing objects -----------------------------------------------------
            myCompany.showObjects();

        } else if (option == 4){
    // Editing pipes -----------------------------------------------------------------------------------------------------------------------
            myCompany.editPipes();
        } else if (option == 5){
    // Editing compressor stations ------------------------------------------------------------------------------------------------------------------
            myCompany.editCompressorStations();
        } else if (option == 6){
    // Saving company to file ---------------------------------------------------------------------------------------------------------------------------
            std::string filename;
            std::cout<<"Enter filename (use .save): ";
            std::cin>>filename;
            myCompany.saveCompany(filename);

        } else if (option == 7){
    // Loading company from file ------------------------------------------------------------------------------------------------------------------------
            std::string filename;
            std::cout<<"Enter filename (use .save): ";
            std::cin>> filename;
            myCompany.loadCompany(filename);

        } else if (option == 8){
    // Finding by filters -------------------------------------------------------------------------------------------------------------------------------
            myCompany.findObjects();
        } else if (option == 9){
            myCompany.unlink();
        } else if (option == 10){
            myCompany.Network.Sort();
        }
    }
    return 0;
}