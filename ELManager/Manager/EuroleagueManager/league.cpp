#include "league.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QIODevice>

league::league()
    :m_round(0)
{

}

league::league(std::vector<team> teams, team myTeam)
    :m_teams(teams), m_myTeam(myTeam), m_round(0)
{

}

void league::setTeams(std::vector<team> t)
{
    m_teams = t;
}

std::vector<team> league::getTeams()const
{
    return m_teams;
}

void league::setMyTeam(team myTeam)
{
    m_myTeam = myTeam;
}

team league::getMyTeam()
{
    return m_myTeam;
}

bool is_market_separator(char c)
{
    return c == ':';
}

std::vector<std::string> playersMarketParse(std::string & line)
{
    std::vector<std::string> res;

    auto i = line.begin();
    while(i != line.end()) {

        i = std::find_if_not(i, line.end(), is_market_separator);

       auto j = std::find_if(i, line.end(), is_market_separator);

        if(i != line.end())
              res.push_back(std::string(i, j));

        i = j;
    }

    return res;
}

void league::set_schedule(std::vector<std::vector<team>> t){
    m_schedule=t;
}
std::vector<std::vector<team>> league::get_schedule()const{
    return m_schedule;
}

void league::setTransferMarket()
{
    QFile file("transferMarket.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {

        QString qLine = in.readLine();
        std::string line = qLine.toStdString(); // line as a string

        std::vector<std::string> data = playersMarketParse(line);

        int number = std::stoi(data[0]);
        std::string name = data[1];
        std::string dateOfBirth = data[2];
        std::string nationality = data[3];
        std::string position = data[4];
        double height = std::stof(data[5]);
        int onePointer = std::stoi(data[6]);
        int twoPointer = std::stoi(data[7]);
        int threePointer = std::stoi(data[8]);
        int assits = std::stoi(data[9]);
        int dribble = std::stoi(data[10]);
        int defence = std::stoi(data[11]);
        int physicality = std::stoi(data[12]);

        player p = player(number, name, dateOfBirth, nationality, position, height, onePointer, twoPointer, threePointer, assits, dribble, defence, physicality);
        //p.toString();
        m_transferMarket.push_back(p);
    }

    // Stampanje igraca
    auto i = m_transferMarket.begin();
    while(i != m_transferMarket.end()) {

        (*i).toString();
        i++;
    }
}

std::vector<player> league::getTransferMarket()
{
    return m_transferMarket;
}

unsigned int league::getRound() const
{
    return m_round;
}

std::vector<team> league::getNextRound()
{
    std::vector<team> nextRound = m_schedule[m_round];

    if(m_round < 6)
        m_round++;

    // if m_round == 6 ====> END GAME

    return nextRound;
}
