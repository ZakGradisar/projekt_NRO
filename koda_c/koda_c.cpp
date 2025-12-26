// NRO_projekt_ŽG_GJ.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> 
#include <iostream>
///svoja  funkcija za iskanje sosedov

#include <vector>
#include <cmath>

// MATLAB blok "Iskanje sosedov vozlisc" -> ena C++ funkcija
std::vector<std::vector<int>> izracunajSosede(
    int n_vozlisc,
    int n_celic,
    const std::vector<double>& X,
    const std::vector<double>& Y,
    const std::vector<int>& c1,
    const std::vector<int>& c2,
    const std::vector<int>& c3,
    const std::vector<int>& c4)
{
    // MATLAB: preveriPozicijo(...) -> C++ lokalno, da ni helperjev zunaj
    auto preveriPozicijo = [](double x0, double y0, double x1, double y1) -> int
        {
            double eps = 1e-9;

            // x enak -> vertikalno
            if (std::fabs(x0 - x1) < eps)
            {
                if (y0 - y1 > 0) return 2; // spodaj
                else return 4;             // zgoraj
            }
            // y enak -> horizontalno
            else if (std::fabs(y0 - y1) < eps)
            {
                if (x0 - x1 > 0) return 1; // levo
                else return 3;             // desno
            }
            return -1; // diagonala ali ne-poravnano
        };

    // MATLAB: sosednja_vozlisca = [];
    std::vector<std::vector<int>> sosednja_vozlisca;
    sosednja_vozlisca.reserve(n_vozlisc);

    // MATLAB: for node_id = 0:n_vozlisc-1
    for (int node_id = 0; node_id < n_vozlisc; node_id++)
    {
        // MATLAB: node_i_neighbours = [-1,-1,-1,-1];
        std::vector<int> node_i_neighbours = { -1, -1, -1, -1 };

        // MATLAB: for nd = 0:n_celic-1
        for (int nd = 0; nd < n_celic; nd++)
        {
            // MATLAB: trenutna_celica = celice(nd,:)
            int vozlisce1 = c1[nd];
            int vozlisce2 = c2[nd];
            int vozlisce3 = c3[nd];
            int vozlisce4 = c4[nd];

            // MATLAB: if node_id je v trenutni celici
            if (node_id == vozlisce1 || node_id == vozlisce2 ||
                node_id == vozlisce3 || node_id == vozlisce4)
            {
                // MATLAB: for vozl = 1:4
                for (int vozl = 0; vozl < 4; vozl++)
                {
                    // MATLAB: sosednje_vozlisce = trenutna_celica(vozl)
                    int sosednje_vozlisce;
                    if (vozl == 0) sosednje_vozlisce = vozlisce1;
                    else if (vozl == 1) sosednje_vozlisce = vozlisce2;
                    else if (vozl == 2) sosednje_vozlisce = vozlisce3;
                    else sosednje_vozlisce = vozlisce4;

                    // MATLAB: if sosednje_vozlisce ~= node_id
                    if (sosednje_vozlisce != node_id)
                    {
                        // MATLAB: x/y trenutnega in soseda
                        double x0 = X[node_id];
                        double y0 = Y[node_id];
                        double x1 = X[sosednje_vozlisce];
                        double y1 = Y[sosednje_vozlisce];

                        // MATLAB: pozicija = preveriPozicijo(...)
                        int pozicija = preveriPozicijo(x0, y0, x1, y1);

                        // MATLAB: if pozicija ~= -1 -> node_i_neighbours(pozicija) = sosednje_vozlisce
                        if (pozicija != -1)
                        {
                            node_i_neighbours[pozicija - 1] = sosednje_vozlisce;
                        }
                    }
                }
            }
        }

        // MATLAB: sosednja_vozlisca = [sosednja_vozlisca; node_i_neighbours]
        sosednja_vozlisca.push_back(node_i_neighbours);
    }

    return sosednja_vozlisca;
}



/// <summary>
///main
/// </summary>
/// <returns></returns>

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

    // Preverim ali smo pragvilno prebrali število celic -> mora biti 2778
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


    // ==========================
    // ROBNI POGOJI
    // ==========================

    std::vector<std::vector<int>> vozlisca_robnih_pogojev;
    std::vector<int> tipi_robnih_pogojev;
    std::vector<double> vrednosti_robnih_pogojev;
    std::vector<double> vrednosti_prestopa_toplote;

  
    std::string robni_pogoji_line;
    std::getline(file, robni_pogoji_line);

    std::istringstream iss_rp(robni_pogoji_line);
    std::string token;
    std::string last_token;
    while (iss_rp >> token) last_token = token;
    int n_pogoji = std::stoi(last_token);

  
    for (int n = 0; n < n_pogoji; n++)
    {
       
        std::string line;
        std::getline(file, line);

        std::istringstream iss_tip(line);
        std::string t1, t2, tip_pogoja;
        iss_tip >> t1 >> t2 >> tip_pogoja; 

      
        if (tip_pogoja == "temperatura")
        {
            tipi_robnih_pogojev.push_back(0);

          
            std::getline(file, line);
            std::istringstream iss(line);
            std::string a;
            double temperatura;
            iss >> a >> temperatura; // 2. token

            vrednosti_robnih_pogojev.push_back(temperatura);
            vrednosti_prestopa_toplote.push_back(-1.0);
        }
        else if (tip_pogoja == "toplotni")
        {
            tipi_robnih_pogojev.push_back(1);

          
            std::getline(file, line);
            std::istringstream iss(line);
            std::string a, b;
            double toplotni_tok;
            iss >> a >> b >> toplotni_tok; // 3. token

            vrednosti_robnih_pogojev.push_back(toplotni_tok);
            vrednosti_prestopa_toplote.push_back(-1.0);
        }
        else if (tip_pogoja == "prestop")
        {
            tipi_robnih_pogojev.push_back(2);

          
            std::getline(file, line);
            std::istringstream iss1(line);
            std::string a;
            double temperatura_prestopa;
            iss1 >> a >> temperatura_prestopa; // 2. token

           
            std::getline(file, line);
            std::istringstream iss2(line);
            std::string b, c;
            double koeficient_prestopa;
            iss2 >> b >> c >> koeficient_prestopa; // 3. token

            vrednosti_robnih_pogojev.push_back(temperatura_prestopa);
            vrednosti_prestopa_toplote.push_back(koeficient_prestopa);
        }

      
        std::getline(file, line);
        int st_vozlisc_v_robnem_pogoju = std::stoi(line);

       
        std::vector<int> vozlisca_v_robnem_pogoju;
        for (int vozl = 0; vozl < st_vozlisc_v_robnem_pogoju; vozl++)
        {
            std::getline(file, line);
            int id_vozlisce_v_robnem_pogoju = std::stoi(line);// lahko das -1, nevem cist tocn kok so vozlišča oznacena
            vozlisca_v_robnem_pogoju.push_back(id_vozlisce_v_robnem_pogoju);
        }

        vozlisca_robnih_pogojev.push_back(vozlisca_v_robnem_pogoju);

        std::getline(file, line);
        }


    // ==========================
	// PREVERJANJE ROBNIH POGOJEV - to je treba zbrisat oz. nardit bol butasto čene bo vedu da je chat, je pa super za preverit
    // ==========================

    // 1) Povzetek vseh robnih pogojev (da vidiš, da jih je 5 in kateri je kateri)
    std::cout << "\nPOVZETEK ROBNIH POGOJEV:\n";
    std::cout << "rp(C++)  rp(MATLAB)  tip  vrednost  h/prestop  st_vozlisc\n";
    std::cout << "--------------------------------------------------------\n";

    for (int k = 0; k < (int)tipi_robnih_pogojev.size(); k++)
    {
        int tip = tipi_robnih_pogojev[k];
        double v = vrednosti_robnih_pogojev[k];
        double h = vrednosti_prestopa_toplote[k];
        int st = (int)vozlisca_robnih_pogojev[k].size();

        std::cout << k << "       "
            << (k + 1) << "          "
            << tip << "    "
            << v << "      "
            << h << "        "
            << st << "\n";
    }

    std::cout << "--------------------------------------------------------\n";

    // 2) Tukaj izbereš kateri robni pogoj hočeš gledati (0..4)
    int rp = 4;  // <-- spremeni na 0,1,2,3,4

    // 3) Izpis izbranega robnega pogoja
    std::cout << "\nIZBRAN ROBNI POGOJ rp = " << rp
        << " (MATLAB rp = " << rp + 1 << ")\n";

    int tip = tipi_robnih_pogojev[rp];
    double v = vrednosti_robnih_pogojev[rp];
    double h = vrednosti_prestopa_toplote[rp];

    if (tip == 0)
    {
        std::cout << "Tip: temperatura (Dirichlet)\n";
        std::cout << "T = " << v << "\n";
    }
    else if (tip == 1)
    {
        std::cout << "Tip: toplotni tok (Neumann)\n";
        std::cout << "q = " << v << "\n";
    }
    else if (tip == 2)
    {
        std::cout << "Tip: prestop (Robin)\n";
        std::cout << "Text = " << v << "\n";
        std::cout << "h = " << h << "\n";
    }
    else
    {
        std::cout << "Tip: neznan (" << tip << ")\n";
        std::cout << "vrednost = " << v << "  h = " << h << "\n";
    }

    int st = (int)vozlisca_robnih_pogojev[rp].size();
    std::cout << "Stevilo vozlisc = " << st << "\n";

    // 4) Izpis prvih N vozlišč + indeks i (točno to, kar želiš)
    int N = 20;
    std::cout << "Prvih " << N << " vozlisc (indeks i + ID):\n";
    for (int i = 0; i < N && i < st; i++)
    {
        int id = vozlisca_robnih_pogojev[rp][i]; // ID iz datoteke (tak kot je)
        std::cout << "  [" << i << "]  id = " << id << "\n";
    }

	// ==========================
	// gradnja MAtrike in vektorja - iskanje sosedov
	// ==========================
    auto sosednja_vozlisca = izracunajSosede(n_vozlisc, n_celic, X, Y, c1, c2, c3, c4);
    
	// Preverimo izračun sosedov za vozlišče 0
    int node_test = 0;
    std::cout << "node " << node_test << " [L,D,R,U] = "
        << sosednja_vozlisca[node_test][0] << ", "
        << sosednja_vozlisca[node_test][1] << ", "
        << sosednja_vozlisca[node_test][2] << ", "
        << sosednja_vozlisca[node_test][3] << "\n";

    return 0;
}

