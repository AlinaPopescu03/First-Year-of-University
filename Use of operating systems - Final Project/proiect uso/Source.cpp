#pragma once

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>


#include <vector>


struct Table_data
{
    std::string numetabel;
    std::vector<bool> tip_coloana; 
    std::vector<std::string> nume_coloane;
    std::vector<std::vector<std::string>> valori_coloane;
};

void creareFisier(std::string command, struct Table_data dates)
{
    std::string aux;
    aux = command;
    aux = aux + ".txt";
    std::ofstream tabel(aux);
    tabel << dates.numetabel << "\n";
    for (int i = 0; i < dates.nume_coloane.size(); i++)
        tabel << dates.nume_coloane[i] << " ";
    tabel << "\n";
    if(dates.valori_coloane.size()!=0)
        for (int i = 0;  i < dates.valori_coloane[0].size(); i++)
    {
        for (int j = 0; j < dates.nume_coloane.size(); j++)
            tabel << dates.valori_coloane[j][i] << " ";
        tabel << "\n";
    }
    tabel.close();
}
void creareFisier2(std::string command, struct Table_data dates)
{
    std::string aux;
    aux = command;
    aux = aux + ".txt";
    std::ofstream tabel(aux);
    tabel << dates.numetabel << "\n";
    for (int i = 0; i < dates.nume_coloane.size(); i++)
        tabel << dates.nume_coloane[i] << " ";
    tabel << "\n";

    tabel.close();
}

struct Table_data citireFisier(std::string filename,struct Table_data dates)
{
    std::string line;
    std::vector<std::string> fileData;

    std::ifstream fisier(filename);

    int ok = 0;

    while (getline(fisier, line))
    {
        std::vector<std::string> dataInsert;
        std::stringstream lineStream(line);
        while (getline(lineStream, line, ' '))
        {
            
                fileData.push_back(line);
        }

        for (int i = 0; i < fileData.size(); i++)
        {
            if (fileData[i] == "")
            {
                fileData.erase(fileData.begin() + i);
                i--;
            }
        }
        if (ok == 0)
        {
            dates.numetabel = fileData[0];
            ok = 1;
            fileData.clear();
        }
        else if (ok == 1)
        {
            for(int i=0;i< fileData.size();i++)
                dates.nume_coloane.push_back(fileData[i]);
            ok = 2;
        }
        else if (ok >= 2)
        {
            if(ok == 2)
                for (int i = 0; i < fileData.size(); i++)
            {
                std::vector<std::string> v1;
                v1.push_back("int");
                std::vector<std::string> v2;
                v2.push_back("varchar");
                if (fileData[i].find("int") != std::string::npos)
                    dates.valori_coloane.push_back(v1);
                else if (fileData[i].find("varchar") != std::string::npos)
                    dates.valori_coloane.push_back(v2);
                ok++;
            }
            else
            {
                for (int j = 0; j < fileData.size(); j++) {
                    if (fileData[j].back() == ',')
                    {
                        dataInsert.push_back(fileData[j]);
                    }
                    else
                    {
                        std::string aux;
                        aux = fileData[j];
                        while (fileData[j].back() != ',' && j<fileData.size()-1)
                        {
                            aux = aux + " ";
                            aux = aux + fileData[j + 1];
                            j++; 
                        }

                        dataInsert.push_back(aux);
                    }

                }
                for (int i = 0; i < dates.nume_coloane.size(); i++)
                    dates.valori_coloane[i].push_back(dataInsert[i]);
            }
        }
        fileData.clear();
    }
    fisier.close();
    return dates;
}

struct Table_data CreateTable(std::vector<std::string> command)
{
    struct Table_data date;
    int nr = 0;
    date.numetabel = command[2];
    
    for (int i = 0; i < command.size(); i++)
    {      
        std::vector<std::string> v1;
        v1.push_back("int");
        std::vector<std::string> v2;
        v2.push_back("varchar");
        if (command[i].find("int") != std::string::npos)
        {
            date.valori_coloane.push_back(v1);
            date.nume_coloane.push_back(command[i - 1]);
            date.tip_coloana.push_back(1);
            nr++;
        }
        else if (command[i].find("varchar") != std::string::npos)
        {
            date.valori_coloane.push_back(v2);
            date.nume_coloane.push_back(command[i-1]);
            date.tip_coloana.push_back(0);
            nr++;
        }
        
    }
   
    return date;
    
}

struct Table_data InsertInto(std::vector<std::string> command, struct Table_data dates)
{
    std::vector<std::string> columnNames;
    std::vector<std::string> dataInsert;
    int p = 0;
    while (command[p] != "INSERT")
            p++;
    std::string aux2;
    aux2 = command[p + 2];
    aux2 = aux2 + " ";
    dates = citireFisier(aux2, dates);
    p = p + 3;
    int aux;
    aux = p;
    while (command[p] != "VALUES")
    {
        columnNames.push_back(command[p]);
        p++;
    }
    p = p + 1;
    while (command[p].back() != ';')
    {
        if (command[p].back() == ',' )
        {
            dataInsert.push_back(command[p]);
            p++;
        }
        else
        {
            std::string aux;
            aux = command[p];
            while (command[p].back() != ',')
            {
                aux = aux + " ";
                aux = aux + command[p + 1];
                p++;
            }
            p++;
            dataInsert.push_back(aux);
        }
    }
    dataInsert.push_back(command[p]);
    for (int i = 0; i < columnNames.size(); i++)
    {
        //columnNames[i].erase(remove(columnNames[i].begin(), columnNames[i].end(), ','), columnNames[i].end());
        columnNames[i].erase(remove(columnNames[i].begin(), columnNames[i].end(), '('), columnNames[i].end());
        columnNames[i].erase(remove(columnNames[i].begin(), columnNames[i].end(), ')'), columnNames[i].end());
    }
    for (int i = 0; i < dataInsert.size(); i++)
    {
        //dataInsert[i].erase(remove(dataInsert[i].begin(), dataInsert[i].end(), ','), dataInsert[i].end());
        dataInsert[i].erase(remove(dataInsert[i].begin(), dataInsert[i].end(), ')'), dataInsert[i].end());
        dataInsert[i].erase(remove(dataInsert[i].begin(), dataInsert[i].end(), '('), dataInsert[i].end());
        dataInsert[i].erase(remove(dataInsert[i].begin(), dataInsert[i].end(), ';'), dataInsert[i].end());
        dataInsert[i].erase(remove(dataInsert[i].begin(), dataInsert[i].end(), '\''), dataInsert[i].end());
    }
    for (int i = 0; i < columnNames.size(); i++)
        for (int j = 0; j < dates.nume_coloane.size(); j++)
            if (columnNames[i].find(dates.nume_coloane[j]) != std::string::npos)
                dates.valori_coloane[j].push_back(dataInsert[i]);
    
    return dates;
    
}

std::vector<std::string> ReadCommand(std::string filename)
{
    std::string line;
    std::vector<std::string> words;

    std::ifstream file(filename);

    while (getline(file, line))
    {
        std::stringstream lineStream(line);
        while (getline(lineStream, line, ' '))
        {
            words.push_back(line);
        }

        for (int i = 0; i < words.size(); i++)
        {
            if (words[i] == "")
            {
                words.erase(words.begin() + i);
                i--;
            }
        }
    }
    file.close();

    return words;
}

void SelectFrom(std::vector<std::string> command, struct Table_data dates)
{
    struct Table_data test;
    int p;
    p = 0;
    while (command[p] != "FROM")
        p++;
    if (command[p + 1].find(dates.numetabel) == std::string::npos)
        std::cout << "Nu exista tabela!";
    else if(command[p-1].back() == '*')
    {
        std::cout << dates.numetabel << "\n";
        for (int i = 0; i < dates.nume_coloane.size(); i++)
            std::cout << dates.nume_coloane[i] << "          ";
        std::cout << "\n";
        for (int i = 0; i < dates.valori_coloane.size(); i++)
        {
            for (int j = 0; j < dates.valori_coloane[i].size(); j++)
                std::cout << dates.valori_coloane[i][j] << "      ";//3
            std::cout << "\n";
        }
    }
    else
    {
        while (command[p - 1] != "SELECT")
            p--;
        while (command[p] != "FROM")
        {
            for (int i = 0; i < dates.nume_coloane.size(); i++)
                if (command[p].find(dates.nume_coloane[i]) != std::string::npos)
                {
                    std::cout << dates.nume_coloane[i] << " ";
                    for (int j = 0; j < dates.valori_coloane[i].size(); j++)
                        std::cout << dates.valori_coloane[i][j] << " ";
                    std::cout << "\n";
                }

            p++;
        }
    }
}

struct Table_data Delete(std::vector<std::string> command, struct Table_data dates)
{
    int p;
    p = 0;
    while (command[p] != "DELETE")
        p++;
    p = p + 2;
    dates.valori_coloane.clear();   
    return dates;
}

struct Table_data Update(std::vector<std::string> command, struct Table_data dates)
{
    std::vector<std::string> numCol;
    std::vector<std::string> valCol;
    std::vector<std::string> Id;
    std::vector<std::string> valId;
    int p = 0;
    while (command[p] != "SET")
        p++;
    p++;
    while (command[p] != "WHERE")
    {
        if (command[p].back() == '=')
        {
            numCol.push_back(command[p]);
            p++;
        }
        else
        {
            if (command[p].back() == '\'' || command[p].back() == ',')
            {
                valCol.push_back(command[p]);
                p++;
            }
            else
            {
                std::string aux;
                aux = command[p];
                while (command[p].back() != ',')
                {
                    aux = aux + " ";
                    aux = aux + command[p + 1];
                    p++;
                }
                valCol.push_back(aux);

                p++;
            }
        }
    }
    p++;
    while (command[p] != "QUIT")
    {
        if (command[p].back() == '=')
        {
            Id.push_back(command[p]);
            p++;
        }
        else
        {
            if (command[p].back() == ';' || command[p].back() == ',')
            {
                if(command[p].back()==';')
                    command[p].erase(remove(command[p].begin(), command[p].end(), ';'), command[p].end());
                valId.push_back(command[p]);
                p++;
            }
            else
            {
                std::string aux;
                aux = command[p];
                while (command[p].back() != ',')
                {
                    if (command[p + 1].back() == ';')
                        command[p + 1].erase(remove(command[p + 1].begin(), command[p + 1].end(), ';'), command[p + 1].end());
                    aux = aux + " ";
                    aux = aux + command[p + 1];
                    p++;
                }
                valId.push_back(aux);

                p++;
            }
        }

    }
    int pozRow;
    std::vector<int> pozCol;
    pozRow = -1;
    for(int i=0;i<valId.size();i++)
        valId[i].erase(remove(valId[i].begin(), valId[i].end(), '\''), valId[i].end());
    for (int i = 0; i < dates.nume_coloane.size(); i++)
        for(int t=0;t<valId.size();t++)
            if (Id[t].find(dates.nume_coloane[i]) != std::string::npos)
            {
                pozRow = i;
                for (int j = 1; j < dates.valori_coloane[0].size(); j++)
                    if (valId[t] == dates.valori_coloane[i][j])
                        pozCol.push_back(j);
            
        }
    if (pozCol.size() > 1) {
        for (int i = 0; i < pozCol.size() - 1; i++)
            if (pozCol[i + 1] <= pozCol[i])
            {
                pozCol.erase(pozCol.begin() + i + 1);
                i--;
            }
    }
    if (pozCol.size() == 0 && pozRow == -1)
        std::cout << "Eroare!";
    else
    {
        for (int i = 0; i < valCol.size(); i++)
            valCol[i].erase(remove(valCol[i].begin(), valCol[i].end(), '\''), valCol[i].end());
        int j = 0;
        for (int i = 0; i < dates.nume_coloane.size(); i++) {
            while (j < numCol.size())
            {
                if (numCol[j].find(dates.nume_coloane[i]) != std::string::npos)
                    for(int t=0;t<pozCol.size();t++)
                        dates.valori_coloane[i][pozCol[t]] = valCol[j];
                j++;
            }
            j = 0; 
        }
        return dates;
    }
}

int main()
{
    int t = 0;
    std::vector<std::string> words = ReadCommand("input.txt");
    struct Table_data dates, test;
    int p = 0;
    std::string aux2;
    while (words[p] != "QUIT")
    {
        if (words[p] == "CREATE")
        {
            dates = CreateTable(words);
            creareFisier(words[p + 2], dates);
        }
        else if (words[p] == "INSERT")
        {
            aux2 = words[p + 2];
            aux2 = aux2 + ".txt";
            std::ifstream filename(aux2);
            if (filename.good())
            {
                dates = citireFisier(aux2, test);
                dates = InsertInto(words, dates);
                creareFisier(words[p + 2], dates);
            }
            else
                std::cout << "Nu exista!";
        }
        else if (words[p] == "SELECT")
        { 
            while (words[p] != "FROM")
                p++;
            aux2 = words[p + 1];
            aux2.erase(remove(aux2.begin(), aux2.end(), ';'), aux2.end());
            aux2 = aux2 + ".txt";
            dates = citireFisier(aux2, test);
            SelectFrom(words, dates);
        }
        else if (words[p] == "DELETE")
        {   
            aux2 = words[p + 2];
            aux2.erase(remove(aux2.begin(), aux2.end(), ';'), aux2.end());
            std::string aux1;
            aux1 = aux2; 
            aux2 = aux2 + ".txt";
            std::ifstream filename(aux2);
            if (filename.good()) {
                dates = citireFisier(aux2, test);
                dates = Delete(words, dates);
                creareFisier(aux1, dates);
            }
            else
                std::cout << "Nu exista tabelul!";
        }
        else if (words[p] == "UPDATE")
        {
            aux2 = words[p + 1];
            aux2 = aux2 + ".txt";
            std::ifstream filename(aux2);
            if (filename.good()) {
                dates = citireFisier(aux2, test);
                dates = Update(words, dates);
                creareFisier(words[p+1], dates);
            }
            else
                std::cout << "Nu exista tabelul!";
        }
        p++;
    }
}