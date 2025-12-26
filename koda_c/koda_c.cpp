// NRO_projekt_ŽG_GJ.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> 
#include <iostream>

int main()
{    //program ki prebere datoteko - GAl
    std::string mapa = "primer3mreza.txt";

    std::vector<double> X;
    std::vector<double> Y;

    std::ifstream file;
    file.open(mapa);


    std::string str_tocke;
    file >> str_tocke;
    std::string str_points;
    file >> str_points;
    int n_vozlisc = std::stoi(str_points);

    // da greš nakonc vrstice
    std::string dummy;
    std::getline(file, dummy);



    for (int i = 0; i < n_vozlisc; i++)
    {
        std::string s;
        std::getline(file, s);

        std::replace(s.begin(), s.end(), ';', ' ');
        std::replace(s.begin(), s.end(), ',', ' ');

        std::istringstream iss(s);
        int node_id;
        double x;
        double y;
        iss >> node_id >> x >> y;

        X.push_back(x);
        Y.push_back(y);
    }


    std::string prazna_vrstica;
    std::getline(file, prazna_vrstica);

    // Preveremi ali smo parv prebrali število toèk -> mora biti 2928
    std::cout << "Stevilo tock = " << X.size() << std::endl;
    // izpišemo prvih 5 toèk za preverjenje
    std::cout << "Prvih 5 tock:" << std::endl;
    for (int i = 0; i < 5 && i < X.size(); i++)
    {
        std::cout << "i = " << i
            << "  x = " << X[i]
            << "  y = " << Y[i] << std::endl;
    }
    // ==========================
// CELICE


    std::string str_celice;
    file >> str_celice;            // "CELICE"
    std::string str_n_celic;
    file >> str_n_celic;           // stevilo celic
    int n_celic = std::stoi(str_n_celic);


    std::string dummy2;
    std::getline(file, dummy2);


    std::vector<int> c1, c2, c3, c4;


    for (int i = 0; i < n_celic; i++)
    {
        std::string s;
        std::getline(file, s);

        std::replace(s.begin(), s.end(), ';', ' ');
        std::replace(s.begin(), s.end(), ',', ' ');

        std::istringstream iss(s);

        int cell_id;
        int n1, n2, n3, n4;

        iss >> cell_id >> n1 >> n2 >> n3 >> n4;

        c1.push_back(n1);
        c2.push_back(n2);
        c3.push_back(n3);
        c4.push_back(n4);
    }


    std::string prazna_vrstica2;
    std::getline(file, prazna_vrstica2);

    // Preverim ali smo prav prebrali število celic -> mora biti 2778
    std::cout << "Stevilo celic = " << c1.size() << std::endl;
    // izpišemo prvih 5 celic za preverjenje
    std::cout << "Prvih 5 celic:" << std::endl;
    for (int i = 0; i < 5 && i < c1.size(); i++)
    {
        std::cout << "i = " << i
            << "  [" << c1[i]
            << ", " << c2[i]
            << ", " << c3[i]
            << ", " << c4[i] << "]"
            << std::endl;
    }
    return 0;
}