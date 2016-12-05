#include "dataloader.h"

dataloader::dataloader()
{
    for (int i = 0 ; i < 120 ; i++)
    {
        for (int j = 0 ; j < 160 ; j++)
        {
            map[i][j].x = i;
            map[i][j].y = j;
            map[i][j].weight = 'E';
        }
    }
}

void dataloader::loader(std::string map_direct, std::string path_direct)
{
    mapReader(map_direct);
    GTDReader(path_direct);

    //DEBUG
    std::cout<< init_coord.first << ',' << init_coord.second << std::endl;
    std::vector<std::pair<int,int>>::iterator it;
    for (it = coord.begin(); it != coord.end(); it++)
    {
        std::pair <int,int> p = *it;
        std::cout << p.first << ',' << p.second << " ";
    }
    std::cout << std::endl;

    std::vector<std::string>::iterator it_a;
    for (it_a = action.begin(); it_a != action.end(); it_a++)
        std::cout << *it_a << " ";
    std::cout << std::endl;

    std::vector<std::string>::iterator it_s;
    for (it_s = sense.begin(); it_s != sense.end(); it_s++)
        std::cout << *it_s << " ";
    std::cout << std::endl;

}

void dataloader::mapReader(std::string path)
{
    std::vector <std::string> svect;
    std::vector <std::string>::iterator it;
    std::ifstream file;
    file.open(path);
    if (file.is_open())
        std::cout << "file is open" << std::endl;
    else
    {
        std::cout << "file fail to open" << std::endl;
        return;
    }

    std::vector <std::string> strVect;

    for (int i = 0; i < 10; i++)
    {
        std::string str;
        std::getline(file, str);

        strVect.push_back(str);
    }
    std::string temp;
    std::getline(file, temp);

    for (int i = 0; i < 120; i++)
    {
        std::string str(160, '0');
        std::getline(file, str);
        svect = split(str, ",");
        it = svect.begin();
        std::string temp;
        for (int j = 0; j < 160 && it != svect.end(); j++, it++)
        {
            temp = *it;
            map[i][j].x = i;
            map[i][j].y = j;

            if (temp == "0")
            {
                map[i][j].weight = 'B';
                map[i][j].type = 'B';
            }
            else if (temp == "1")
            {
                map[i][j].weight = 'N';
                map[i][j].type = 'N';
            }
            else if (temp == "2")
            {
                map[i][j].weight = 'T';
                map[i][j].type = 'T';
            }
            else if (temp.find("a") != std::string::npos)
            {
                map[i][j].weight = 'H';
                map[i][j].type = 'H';
            }
            else if (temp.find("b") != std::string::npos)
            {
                map[i][j].weight = 'H';
                map[i][j].type = 'H';
            }
        }
    }
    file.close();
}

void dataloader::GTDReader(std::string path)
{
    std::vector <std::string> scoord;
    std::vector <std::string> saction;
    std::vector <std::string> ssense;
    std::vector <std::string>::iterator it;
    std::ifstream file;
    file.open(path);
    if (file.is_open())
        std::cout << "file is open" << std::endl;
    else
    {
        std::cout << "file fail to open" << std::endl;
        return;
    }

    std::string temp;
    std::getline(file, temp);
    init_coord.first = std::stoi(temp.substr(0,temp.find(',')));
    init_coord.second = std::stoi(temp.substr(temp.find(',')+1));

    std::string recv_coord;
    std::getline(file, recv_coord);

    scoord = split(recv_coord, " ");

    for (it = scoord.begin(); it != scoord.end(); it++)
    {
        std::pair <int,int> p;
        std::string s = *it;
        p.first = std::stoi(s.substr(0, s.find(',')));
        p.second = std::stoi(s.substr(s.find(',')+1));
        coord.push_back(p);
    }

    std::string recv_action;
    std::getline(file, recv_action);

    saction = split(recv_action, " ");
    for (it = saction.begin(); it != saction.end(); it++)
        action.push_back(*it);

    std::string recv_sense;
    std::getline(file, recv_sense);

    ssense = split(recv_sense, " ");
    for (it = ssense.begin(); it != ssense.end(); it++)
        sense.push_back(*it);

    file.close();

}

std::vector <std::string> dataloader::split(std::string s, std::string delim)
{
    std::vector <std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0)
        return elems;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}
