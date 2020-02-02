#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QApplication>

#define PORT 2048
#define Path_DB "/home/bobi/Desktop/TopMusic/DataBaseTM.db"
#define valueMSG 10000

static QSqlDatabase db;

void splitTokensAddSong(std::string message,std::string &command,std::string &nameSong,std::string &urlSong,std::string &genreSong, std::string &descSong, std::string &author){
    char str[1000];
    strcpy(str,message.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    nameSong = token;
    token = strtok(nullptr, "#^");
    urlSong = token;
    token = strtok(nullptr, "#^");
    genreSong = token;
    token = strtok(nullptr, "#^");
    descSong = token;
    token = strtok(nullptr, "#^");
    author = token;
}

void splitTokens(std::string message,std::string &command,std::string &user,std::string &pass){
       char str[1000];
       strcpy(str,message.data());
       char *token = strtok(str, " ");
       command = token;
       token = strtok(nullptr, " ");
       user = token;
       token = strtok(nullptr, " ");
       pass = token;
}

std::string login(std::string user,std::string pass){
    std::string acces;
    QSqlQuery qry;
    qry.prepare("SELECT Username, Password, Acces from loginTable WHERE Username = ? and Password = ?");
    qry.addBindValue(QVariant(user.data()));
    qry.addBindValue(QVariant(pass.data()));
    qry.exec();
    if(qry.next())
        return qry.value(2).toString().toStdString();
    return "false";
}

std::string verifyRegister(std::string user){
    std::string acces;
    QSqlQuery qry;
    qry.prepare("SELECT Username, Password, Acces from loginTable WHERE Username = ?");
    qry.addBindValue(QVariant(user.data()));
    qry.exec();
    if(qry.next())
        return qry.value(2).toString().toStdString();
    return "false";
}

std::string verifyAddSong(std::string nameSong,std::string urlSong){
    QSqlQuery qry;
    qry.prepare("SELECT No, Name from songList WHERE Name = ?");
    qry.addBindValue(QVariant(nameSong.data()));
    qry.exec();
    if(qry.next())
        return qry.value(2).toString().toStdString();

    qry.prepare("SELECT No, Name from songList WHERE Url = ?");
    qry.addBindValue(QVariant(urlSong.data()));
    qry.exec();
    if(qry.next())
        return qry.value(0).toString().toStdString();

    return "false";
}

void addRegister(std::string user,std::string pass){
    int no;
    QSqlQuery qry;
    qry.prepare("SELECT count(1) from loginTable");
    qry.exec();
    qry.next();
    no=qry.value(0).toInt() + 1;

    QSqlQuery query;
    query.prepare( "INSERT INTO loginTable VALUES(?, ?, ?, ?, ?)" );
    query.addBindValue(no);
    query.addBindValue(user.data());
    query.addBindValue(pass.data());
    query.addBindValue("user");
    query.addBindValue(1);
    query.exec();
}

void addSongInBase(std::string nameSong,std::string urlSong,std::string genreSong,std::string descSong,std::string author){
    int no;
    QSqlQuery qry;
    qry.prepare("select No from songList order by No desc LIMIT 1");
    qry.exec();
    qry.next();
    no=qry.value(0).toInt() + 1;

    QSqlQuery query;
    query.prepare( "INSERT INTO songList VALUES(?, ?, ?, ?, ?, ?, ?)" );
    query.addBindValue(no);
    query.addBindValue(nameSong.data());
    query.addBindValue(descSong.data());
    query.addBindValue(0);
    query.addBindValue(urlSong.data());
    query.addBindValue(genreSong.data());
    query.addBindValue(author.data());
    query.exec();
}

std::string showTopSong(){

    std::string concatString;
    QSqlQuery qry;
    qry.prepare("select Likes || '#!' || Name || '#!' || Desc || '#!' || Gen || '#!' || Url || '#!' from songList order by Likes desc LIMIT 10");
    qry.exec();
    while(qry.next())
    concatString = concatString + qry.value(0).toString().toStdString();
    return concatString;
}

std::string showTopSongByGen(std::string genre){

    std::string concatString;
    QSqlQuery qry;
    qry.prepare("select Likes || '#!' || Name || '#!' || Desc || '#!' || Gen || '#!' || Url || '#!' from songList where Gen like ? order by Likes desc LIMIT 10");
    qry.addBindValue(genre.data());
    qry.exec();
    while(qry.next())
    concatString = concatString + qry.value(0).toString().toStdString();
    return concatString;
}

std::string myTop(std::string username){
    char str[1000];
    strcpy(str,username.data());
    char *token = strtok(str, " ");
    token = strtok(nullptr, " ");

    std::string concatString;
    QSqlQuery qry;
    qry.prepare("select Likes || '#!' || Name || '#!' || Desc || '#!' || Gen || '#!' || Url || '#!' from songList where Author like ? order by Likes desc LIMIT 10");
    qry.addBindValue(token);
    qry.exec();
    while(qry.next())
    concatString = concatString + qry.value(0).toString().toStdString();
    return concatString;
}

std::string addVoteSong(std::string answer){
    char str[1000];
    std::string command,name,link,author;
    strcpy(str,answer.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    if(command == "voteSongByName")
        name = token;
    else
        link = token;
    token = strtok(nullptr, "#^");
    author = token;

    int flag = 0; //nu exista in baza

    QSqlQuery qry;

    int acces;
    qry.prepare("SELECT Vote from loginTable where Username = ?");
    qry.addBindValue(QVariant(author.data()));
    qry.exec();
    qry.next();
    acces = qry.value(0).toInt();

    if(acces == 0)
        return "noAcces";

    if(command == "voteSongByName"){

        qry.prepare("SELECT Url from songList WHERE Name = ?");
        qry.addBindValue(QVariant(name.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            link = qry.value(0).toString().toStdString();
        }
    }
    else {
        qry.prepare("SELECT Name from songList WHERE Url = ?");
        qry.addBindValue(QVariant(link.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            name = qry.value(0).toString().toStdString();
     }
        }
       if(flag == 0)
           return "songNotInDB";
       else {
           int flag2 = 0; //daca votul nu e in baza de date
           qry.prepare("SELECT Author, Name, Link from voteBase WHERE Author = ? and Name = ? and Link = ?");
           qry.addBindValue(QVariant(author.data()));
           qry.addBindValue(QVariant(name.data()));
           qry.addBindValue(QVariant(link.data()));
           qry.exec();
           if(qry.next())
               flag2 = 1;

           if (flag2 == 1)
               return "alreadyVoted";
           else {
               QSqlQuery query;
               query.prepare( "INSERT INTO voteBase VALUES(?, ?, ?)" );
               query.addBindValue(author.data());
               query.addBindValue(name.data());
               query.addBindValue(link.data());
               query.exec();

               int updateLikes;
               qry.prepare("SELECT Likes from songList where Name = ? and Url = ?");
               qry.addBindValue(QVariant(name.data()));
               qry.addBindValue(QVariant(link.data()));
               qry.exec();
               qry.next();
               updateLikes = qry.value(0).toInt() + 1;

               qry.prepare("UPDATE songList SET Likes = ? where Name = ? and Url = ?");
               qry.addBindValue(updateLikes);
               qry.addBindValue(QVariant(name.data()));
               qry.addBindValue(QVariant(link.data()));
               qry.exec();

               return "succesAddVote";
           }
       }
}

std::string removeVoteSong(std::string answer){
    char str[1000];
    std::string command,name,link,author;
    strcpy(str,answer.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    if(command == "rmVoteSongByName")
        name = token;
    else
        link = token;
    token = strtok(nullptr, "#^");
    author = token;

    int flag = 0; //nu exista in baza

    QSqlQuery qry;

    int acces;
    qry.prepare("SELECT Vote from loginTable where Username = ?");
    qry.addBindValue(QVariant(author.data()));
    qry.exec();
    qry.next();
    acces = qry.value(0).toInt();

    if(acces == 0)
        return "noAcces";

    if(command == "rmVoteSongByName"){

        qry.prepare("SELECT Url from songList WHERE Name = ?");
        qry.addBindValue(QVariant(name.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            link = qry.value(0).toString().toStdString();
        }
    }
    else {
        qry.prepare("SELECT Name from songList WHERE Url = ?");
        qry.addBindValue(QVariant(link.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            name = qry.value(0).toString().toStdString();
     }
        }
       if(flag == 0)
           return "songNotInDB";
       else {
           int flag2 = 0; //daca votul nu e in baza de date
           qry.prepare("SELECT Author, Name, Link from voteBase WHERE Author = ? and Name = ? and Link = ?");
           qry.addBindValue(QVariant(author.data()));
           qry.addBindValue(QVariant(name.data()));
           qry.addBindValue(QVariant(link.data()));
           qry.exec();
           if(qry.next())
               flag2 = 1;

           if (flag2 == 0)
               return "notVoted";
           else {
               QSqlQuery query;
               query.prepare( "delete from voteBase where Author = ? and Name = ? and Link = ?" );
               query.addBindValue(author.data());
               query.addBindValue(name.data());
               query.addBindValue(link.data());
               query.exec();

               int updateLikes;
               qry.prepare("SELECT Likes from songList where Name = ? and Url = ?");
               qry.addBindValue(QVariant(name.data()));
               qry.addBindValue(QVariant(link.data()));
               qry.exec();
               qry.next();
               updateLikes = qry.value(0).toInt() - 1;

               qry.prepare("UPDATE songList SET Likes = ? where Name = ? and Url = ?");
               qry.addBindValue(updateLikes);
               qry.addBindValue(QVariant(name.data()));
               qry.addBindValue(QVariant(link.data()));
               qry.exec();

               return "succesRemoveVote";
           }
       }
}

std::string addComms(std::string answer){
    //addCommByName#^ addCommByName#^

    char str[1000];
    std::string command,name,link,author,comment;
    strcpy(str,answer.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    if(command == "addCommByName")
        name = token;
    else
        link = token;
    token = strtok(nullptr, "#^");
    comment = token;
    token = strtok(nullptr, "#^");
    author = token;

    int flag = 0; //nu exista in baza
    QSqlQuery qry;

    if(command == "addCommByName"){

        qry.prepare("SELECT Url from songList WHERE Name = ?");
        qry.addBindValue(QVariant(name.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            link = qry.value(0).toString().toStdString();
        }
    }
    else {
        qry.prepare("SELECT Name from songList WHERE Url = ?");
        qry.addBindValue(QVariant(link.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            name = qry.value(0).toString().toStdString();
     }
        }
       if(flag == 0)
           return "songNotInDB";
       else {
           QSqlQuery query;
           query.prepare( "INSERT INTO commentBase VALUES(?, ?, ?, ?)" );
           query.addBindValue(author.data());
           query.addBindValue(name.data());
           query.addBindValue(comment.data());
           query.addBindValue(link.data());
           query.exec();

           return "succesAddComm";
       }

}

std::string showComms(std::string answer){
    //showCommByName#^ showCommByLink#^

    char str[1000];
    std::string command,name,link;
    std::string concatString;

    strcpy(str,answer.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    if(command == "showCommByName")
        name = token;
    else
        link = token;

    int flag = 0; //nu exista in baza
    QSqlQuery qry;

    if(command == "showCommByName"){

        qry.prepare("SELECT Url from songList WHERE Name = ?");
        qry.addBindValue(QVariant(name.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            link = qry.value(0).toString().toStdString();
        }
    }
    else {
        qry.prepare("SELECT Name from songList WHERE Url = ?");
        qry.addBindValue(QVariant(link.data()));
        qry.exec();
        if(qry.next()){
            flag = 1; //exista
            name = qry.value(0).toString().toStdString();
     }
        }
       if(flag == 0)
           return "songNotInDB";
       else {

           concatString = concatString + name + "#!" + link + "#!";

           qry.prepare("select Author || '#!' || Comment || '#!' from commentBase where Name like ? and Url like ?");
           qry.addBindValue(name.data());
           qry.addBindValue(link.data());
           qry.exec();
           while(qry.next())
           concatString = concatString + qry.value(0).toString().toStdString();
           return concatString;
       }


}

std::string banUnban(std::string answer){
    std::string command,user;
    char str[1000];
    strcpy(str,answer.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    user = token;

    std::cout<<command<<std::endl;
    std::string acces;
    QSqlQuery qry,query;
    qry.prepare("SELECT Acces from loginTable WHERE Username = ? ");
    qry.addBindValue(QVariant(user.data()));
    qry.exec();
    if(qry.next()){
        acces = qry.value(0).toString().toStdString();
        if(acces == "admin")
            return "commandDenied";
        else {
            query.prepare("UPDATE loginTable SET Acces = ? where Username = ? ");
            if(command == "ban")
                query.addBindValue(QVariant("banned"));
            else
                query.addBindValue(QVariant("user"));
            query.addBindValue(QVariant(user.data()));
            query.exec();
            return "commandTrue";
        }
    }
    return "false";
}

std::string removeSongFunction(std:: string answer){
    char str[1000];
    std::string command,song;
    strcpy(str,answer.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    song = token;

    std::string acces;
    QSqlQuery qry;

    if(command == "removeSongByName"){
    qry.prepare("SELECT Name from songList WHERE Name = ?");
    qry.addBindValue(QVariant(song.data()));
    qry.exec();
    if(qry.next()){

        QSqlQuery query;
        query.prepare( "delete from songList where Name = ?" );
        query.addBindValue(song.data());
        query.exec();
        return "removeSongTrue";
    }
    }

    if(command == "removeSongByLink"){
    qry.prepare("SELECT Name from songList WHERE Url = ?");
    qry.addBindValue(QVariant(song.data()));
    qry.exec();
    if(qry.next()){

        QSqlQuery query;
        query.prepare( "delete from songList where Url = ?" );
        query.addBindValue(song.data());
        query.exec();
        return "removeSongTrue";
    }
    }
        return "false";
}

std::string setAcces(std::string answer){
    std::string user,command,voteAcces,levelAcces;
    int vote;
    char str[1000];
    strcpy(str,answer.data());
    char *token = strtok(str, "#^");
    command = token;
    token = strtok(nullptr, "#^");
    user = token;
    token = strtok(nullptr, "#^");
    levelAcces = token;
    token = strtok(nullptr, "#^");
    voteAcces = token;


    QSqlQuery qry;
    qry.prepare("SELECT No from loginTable WHERE Username = ?");
    qry.addBindValue(QVariant(user.data()));
    qry.exec();
    if(qry.next()){
        if(voteAcces =="TRUE")
            vote = 1;
        else  vote = 0;
        if(levelAcces == "ADMIN")
            levelAcces = "admin";
        else  levelAcces = "user";

         QSqlQuery query;
          query.prepare("UPDATE loginTable SET Acces = ?, Vote = ? where Username = ? ");
          query.addBindValue(QVariant(levelAcces.data()));
          query.addBindValue(QVariant(vote));
          query.addBindValue(QVariant(user.data()));
          query.exec();
          return "setAccesTRUE";
    }
        return "false";
}

int main ()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Path_DB);
    QSqlDatabase::database();
    if(db.isOpen())
       std::cout<<"<!> S-a reusit conectiunea la baza de date!"<<std::endl;

   struct sockaddr_in server;
   struct sockaddr_in from;

   char msg[valueMSG];
   int sd;			//sd - descriptorul de socket

   if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
   {
       perror ("<!> [SERVER_ERROR]Probleme cu socketul!\n");
       return errno;
   }

   bzero (&server, sizeof (server));
   bzero (&from, sizeof (from));
   server.sin_port = htons (PORT);
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = htonl (INADDR_ANY);


   if (bind(sd,(struct sockaddr *) &server, sizeof(struct sockaddr)) == -1)
   {
       perror ("<!> [SERVER_ERROR] Probleme cu bindurile.\n");
       return errno;
   }

   /* se verifica viitoarele conectiuni */
   if (listen (sd, 1) == -1)
   {
       perror ("<!> [SERVER_ERROR]Probleme la listen!\n");
       return errno;
   }

   /* servim in mod concurent clientii... */
   while (1)
   {
       int client;
       socklen_t length = sizeof (from);

       printf ("<!> [SERVER_INFO] Asteptam sa se realizeze conectiunea cu viitorul client la portul cu numarul %d...\n",PORT);
       fflush (stdout);

       client = accept(sd,(struct sockaddr *) &from, &length);

       if (client < 0)
       {
           perror ("<!> [SERVER_ERROR] Probleme la acceptare!\n");
           continue;
       }

       int pid = fork();
       if (pid  == -1) {
           close(client);
           continue;
       } else if (pid > 0) {
           // parinte
           close(client);
           while(waitpid(-1,nullptr,WNOHANG));
           continue;
       } else if (pid == 0) {




           int childFlag = 1;
           int errorFlag=0;

           std::cout<<"<!> [SERVER_INFO] S-a realizat cu succes conectiunea dintre server si client!"<<std::endl;
           while(childFlag){

           if(errorFlag == 10)
               childFlag = 0;
        std::string answer;

           bzero (msg, valueMSG);
           printf ("<!> [SERVER_INFO] Asteptam comanda de la client\n");
           fflush (stdout);


           if (read (client, msg, valueMSG) <= 0)
           {
               errorFlag++;
               perror ("<!> [SERVER_ERROR] Probleme cu citirea de la client!\n");
               close (client);
               continue; //
           }
           std::string message;
           std::string command,user,pass;
           std::string nameSong,urlSong,genreSong,descSong,author;

           message = msg;
           printf ("<!>[SERVER_INFO] Mesajul primit de la client este: %s\n", msg);
           if(message.find("register ") !=std::string::npos || message.find("login ") !=std::string::npos){
               splitTokens(message,command,user,pass);
               //std::cout<<"DUPA SPLITTOKENS AVEM:"<<std::endl<<message<<std::endl<<command<<std::endl<<user<<std::endl<<pass<<std::endl;
           }
           else if(message.find("addSong#^") != std::string::npos){
               splitTokensAddSong(message,command,nameSong,urlSong,genreSong,descSong,author);
              // std::cout<<"DUPA SPLITTOKENS ADDSONG AVEM:"<<std::endl<<message<<std::endl<<command<<std::endl<<nameSong<<std::endl<<urlSong
                   //    <<std::endl<<genreSong<<std::endl<<descSong<<std::endl<<author<<std::endl;
               /*if( verifyAddSong(nameSong,urlSong) == "false"){
                   addSongInBase(nameSong,urlSong,genreSong,descSong,author);
                   answer = "addSongTRUE";}
               else {
                   answer = "addSongFALSE";
               }
               write (client, answer.data(), answer.length());*/
           }
           else if(message.find("exitMode") != std::string::npos){
           childFlag = 0;
           }
           else if(message.find("showGeneralTop") != std::string::npos){
              // std::cout<<"showgeneraltop"<<std::endl;
               answer = showTopSong();
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Rock") != std::string::npos){
               //std::cout<<"showgeneraltop"<<std::endl;
               answer = showTopSongByGen("Rock");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Chill") != std::string::npos){
               answer = showTopSongByGen("Chill");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Indie") != std::string::npos){
               answer = showTopSongByGen("Indie");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Latino") != std::string::npos){
               answer = showTopSongByGen("Latino");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Manele") != std::string::npos){
               answer = showTopSongByGen("Manele");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("HipHop") != std::string::npos){
               answer = showTopSongByGen("Hip-Hop");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Electro") != std::string::npos){
               answer = showTopSongByGen("Electro");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Populara") != std::string::npos){
               answer = showTopSongByGen("Populara");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if(message.find("Pop") != std::string::npos){
               //std::cout<<"showgeneraltop"<<std::endl;
               answer = showTopSongByGen("Pop");
               if(answer == "")
                   answer = "FailedToShowTop";
               write (client, answer.data(), answer.length());
           }
           else if (message.find("myTop ") != std::string::npos){
               answer = myTop(message);
               if(answer == "")
                   answer = "FailedToShowMyTop";
               write (client, answer.data(), answer.length());
           }
           else if (message.find("voteSongBy") != std::string::npos){
               answer = addVoteSong(message);
               write (client, answer.data(), answer.length());
           }
           else if (message.find("rmVoteSongBy") != std::string::npos){
               answer = removeVoteSong(message);
               write (client, answer.data(), answer.length());
           }
           else if (message.find("addCommBy") != std::string::npos){
               answer = addComms(message);
               write (client, answer.data(), answer.length());
           }
           else if (message.find("showCommBy") != std::string::npos){
               answer = showComms(message);
               if(answer == "")
                   answer = "noComments";
               write (client, answer.data(), answer.length());
           }
           else if (message.find("ban#^") != std::string::npos){
               answer = banUnban(message);
               write (client, answer.data(), answer.length());
           }
           else if(message.find("removeSongBy") != std::string::npos){
               answer = removeSongFunction(message);
               write (client, answer.data(), answer.length());
           }
           else if (message.find("setAcces#^") != std::string::npos) {
               answer = setAcces(message);
               write (client, answer.data(), answer.length());
           }

           //LOGIN
           if(command == "login"){
               if( login(user,pass) != "false"){
                   answer = login(user,pass);
                   write (client, answer.data(), answer.length());
               }

               else {
                    answer = "no";
                    write (client, answer.data(), answer.length());
               }
           }
           //REGISTER
           else if (command == "register"){
               if( verifyRegister(user) == "false"){
                   addRegister(user,pass);
                   answer = "registerTRUE";}
               else {
                   answer = "registerFALSE";
               }
               write (client, answer.data(), answer.length());
}
           //ADD SONG
           else if (command == "addSong"){
               if( verifyAddSong(nameSong,urlSong) == "false"){
                   addSongInBase(nameSong,urlSong,genreSong,descSong,author);
                   answer = "addSongTRUE";}
               else {
                   answer = "addSongFALSE";
               }
               write (client, answer.data(), answer.length());
           }

           if(answer.length() != 0){
           std::cout<<"<!>[SERVER_INFO] Se proceseaza informatia..."<<std::endl;
           std::cout<<"<!> [SERVER_INFO] Mesajul a fost procesat cu succes!"<<std::endl;
           std::cout<<"<!> [SERVER_INFO] Am trimis mesajul:"<<answer<<std::endl;
           std::cout<<std::endl<<"#############################################"<<std::endl;}


}
           if(errorFlag == 10){
               printf("\033c");
               std::cout<<"<!> [SERVER_WARNING] Conectiunea dintre client si server a fost oprita fortat!"<<std::endl;
               std::cout<<"<!> [SERVER_INFO] Se asteapta un nou client..."<<std::endl;
           }
           else{
           printf("\033c");
           std::cout<<"<!> [SERVER_INFO] Conectiunea dintre client si server a fost oprita."<<std::endl;
           std::cout<<"<!> [SERVER_INFO] Se asteapta un nou client..."<<std::endl;

       }
           db.close();
           close (client);
           exit(0);
    }
   }
}
