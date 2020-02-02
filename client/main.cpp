#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include "login.h"
#include <registertime.h>
#include <usermenu.h>
#include "showtopgeneral.h"
#include "showcommwindow.h"



#define port 2048
#define value 30000

int main (int argc, char **argv)
{
    std::string IP = "127.0.0.1";
    QApplication app (argc, argv);
     login loginWindow;
     loginWindow.show();

  std::string answer = "no";
  std::string answerLogIN = "";
  int sd; // sd - descriptorul de socket
  struct sockaddr_in server;
  char msg[value];


  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("<!> [SERVER_ERROR] Socket problem.\n");
      return errno;
    }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(IP.data());
  server.sin_port = htons (port);


  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("<!> [CLIENT_ERROR] Nu s-a reusit conectarea la server!\n");
      return errno;
    }

  int flag = 0;
// login && register
for(;;){
    if(loginWindow.regAnswer.length() == 0){
        loginWindow.show();
        app.exec();}
  if(loginWindow.closeValue == "false"){

      // REGISTER
      if(loginWindow.regAnswer.length() != 0)
      {

       write (sd, loginWindow.regAnswer.data(), 100);
       bzero (msg, 100);
       read (sd, msg, value);
       answer = msg;

       if (answer == "registerFALSE"){
           loginWindow.regAnswer = "";
           QMessageBox::warning(nullptr,"FAILED TO REGISTER!","Username-ul este deja utilizat! Incearca din nou cu alt user");
           loginWindow.show();
           app.exec();
       }
           else
           if (answer == "registerTRUE"){
               loginWindow.regAnswer = "";
           QMessageBox::information(nullptr,"REGISTERED!","Te-ai inregistrat cu succes!");
           loginWindow.show();
           app.exec();

           }
       }

if(loginWindow.username != "" && loginWindow.password != "" ){


  answer = "login " + loginWindow.username + " " + loginWindow.password ;
  write (sd, answer.data(), answer.length());

  bzero (msg, 100);
  read (sd, msg, value);
  answerLogIN = msg ;
  if(answerLogIN == "admin" || answerLogIN == "user" || answerLogIN == "banned")
  {
      flag = 1;
      QMessageBox::information(nullptr,"YOU'RE IN !","You have successfully logged in!");
  }
  else {
      QMessageBox::warning(nullptr,"FAILED TO LOGIN !","Username or Password is incorrect! Please try again.");

      loginWindow.show();
      app.exec();

  }
  }
}

  if(loginWindow.closeValue == "true"){

      flag = 2;
      QMessageBox::warning(nullptr,"BYE BYE","We'll miss you :(");
      answer = "exitMode";
      write (sd, answer.data(), answer.length());
                   }

  if (flag != 0)
      break;

}

// menu
if (answerLogIN == "user" || answerLogIN == "admin")
    while(1){
          userMenu userMenu(loginWindow.username,answerLogIN);

         // userMenu.setWindowFlags(Qt::FramelessWindowHint);
          userMenu.show();
          app.exec();
          bzero(msg,value);

                if(userMenu.addSong != ""){
             userMenu.addSong = userMenu.addSong + "#^" + loginWindow.username;

             write (sd, userMenu.addSong.data(), userMenu.addSong.length());
             bzero (msg, value);
             read (sd, msg, value);
             answer = msg;

             if(answer == "addSongTRUE")
                 QMessageBox::information(nullptr,"ADD SONG","Melodia a fost adaugata cu succes!");
             else {
                 QMessageBox::warning(nullptr,"ADD SONG","Melodia se afla deja in baza de date!");
             }

}
           else if(userMenu.menuCloseFlag == 1){
            QMessageBox::warning(nullptr,"BYE BYE","We'll miss you :(");
            answer = "exitMode";
            write (sd, answer.data(), answer.length());
            break;}
           else if(userMenu.showFLAG == 1){
             if(userMenu.showGeneralTopFlag == 1)
                answer = "showGeneralTop";
             else if (userMenu.showGeneralTopPop == 1)
                 answer = "Pop";
             else if (userMenu.showGeneralTopRock == 1)
                answer = "Rock";
             else if (userMenu.showGeneralTopChill == 1)
                answer = "Chill";
             else if (userMenu.showGeneralTopIndie == 1)
                answer = "Indie";
             else if (userMenu.showGeneralTopLatino == 1)
                answer = "Latino";
             else if (userMenu.showGeneralTopManele == 1)
                answer = "Manele";
             else if (userMenu.showGeneralTopHipHop == 1)
                answer = "HipHop";
             else if (userMenu.showGeneralTopElectro == 1)
                answer = "Electro";
             else if (userMenu.showGeneralTopPopulara == 1)
                answer = "Populara";
             else if (userMenu.showGeneralTopMY == 1)
                answer = "myTop " + loginWindow.username;


             write (sd, answer.data(), answer.length());
             bzero (msg, 100);
             read (sd, msg, value);
             answer = msg;
             if(answer != "FailedToShowTop" && answer != "FailedToShowMyTop" ){
            std::cout<<answer<<std::endl;
             showTopGeneral showTopGeneral(answer);
            // showTopGeneral.setWindowFlags(Qt::FramelessWindowHint);
             showTopGeneral.show();
             app.exec();
             }
             else if (answer == "FailedToShowMyTop"){
                 QMessageBox::warning(nullptr,"TOP Indisponibil","Nu ai melodii adaugate! Adauga o melodie chiar acum!");
             }

             else {
                 QMessageBox::warning(nullptr,"TOP Indisponibil","In top nu se afla nici o melodie de acest gen. Fii primul care adauga una!");
             }
         }
           else if (userMenu.voteSong != ""){
            userMenu.voteSong = userMenu.voteSong + "#^" + loginWindow.username;
            write (sd, userMenu.voteSong.data(), userMenu.voteSong.length());
            bzero (msg, 100);
            read (sd, msg, value);
            answer = msg;

            if(answer =="songNotInDB")
                QMessageBox::warning(nullptr,"Vote / Remove Vote","Melodia nu se afla in baza de date!");
            else if (answer == "alreadyVoted")
                QMessageBox::warning(nullptr,"Vote / Remove Vote","Deja ai votat aceasta melodie!");
            else if (answer == "succesAddVote")
                QMessageBox::information(nullptr,"Vote / Remove Vote","Votul tau a fost adaugat cu succes!");
            else if (answer == "notVoted")
                QMessageBox::warning(nullptr,"Vote / Remove Vote","Nu ai votat aceasta melodie!");
            else if (answer == "succesRemoveVote")
                QMessageBox::information(nullptr,"Vote / Remove Vote","Votul tau a fost sters cu succes!");
            else if (answer == "noAcces")
                QMessageBox::warning(nullptr,"Vote / Remove Vote","Ai accesul restrictionat! Te rog contacteaza stafful!");
         }
           else if (userMenu.addComms != ""){
             userMenu.addComms = userMenu.addComms + "#^" + loginWindow.username;
             write (sd, userMenu.addComms.data(), userMenu.addComms.length());
             bzero (msg, value);
             read (sd, msg, value);
             answer = msg;

             if(answer =="songNotInDB")
                 QMessageBox::warning(nullptr,"ADD COMM","Melodia nu se afla in baza de date!");
             else if (answer == "succesAddComm")
                   QMessageBox::information(nullptr,"ADD COMM","Comentariul tau a fost adaugat cu succes!");

         }
           else if (userMenu.showComms != ""){
             write (sd, userMenu.showComms.data(), userMenu.showComms.length());
             bzero (msg, value);
             read (sd, msg, value);
             answer = msg;

             if(answer == "noComments")
                 QMessageBox::warning(nullptr,"TM - WARNING","Aceasta melodie nu contine comentarii!");
            else if (answer == "songNotInDB")
                 QMessageBox::warning(nullptr,"SHOW COMMS","Melodia nu se afla in baza de date!");
             else{
             showcommwindow showcommwindow(answer);
             showcommwindow.show();
             app.exec();
             }
}
           else if (userMenu.banCommand != ""){
             write (sd, userMenu.banCommand.data(), userMenu.banCommand.length());
             bzero (msg, value);
             read (sd, msg, value);
             answer = msg;

             if(answer == "commandTrue")
                 QMessageBox::information(nullptr,"BAN / UNBAN USER","Comanda a fost realizata cu succes!");
             else if(answer == "commandDenied")
                 QMessageBox::warning(nullptr,"BAN / UNBAN USER","Nu poti modifica accesul unui alt admin!");
             else
                  QMessageBox::warning(nullptr,"BAN / UNBAN USER","Acest user nu se afla in baza de date!");
         }
           else if (userMenu.removeaSong != ""){
             write (sd, userMenu.removeaSong.data(), userMenu.removeaSong.length());
             bzero (msg, value);
             read (sd, msg, value);
             answer = msg;

             if(answer == "removeSongTrue")
                 QMessageBox::information(nullptr,"TM - REMOVE SONG","Melodia a fost stearsa!");
             else
                 QMessageBox::warning(nullptr,"TM - REMOVE SONG","Melodia nu se afla in baza de date!");

         }
           else if (userMenu.setAcces != ""){
             write (sd, userMenu.setAcces.data(), userMenu.setAcces.length());
             bzero (msg, value);
             read (sd, msg, value);
             answer = msg;
             if(answer == "setAccesTRUE")
                 QMessageBox::information(nullptr,"TM - SET ACCES","Gradele de acces au fost actualizate cu succes!");
             else
                 QMessageBox::warning(nullptr,"TM - SET ACCES","Acest utilizator nu este inregistrat!");

         }


}

// cont banat
    if(answerLogIN == "banned")
        QMessageBox::warning(nullptr,"Suspended!","Your account is currently suspended. For more information please contact our support team!");

    std::cout<<"<!> Se inchide conectiunea la serverul cu IP: "<<IP<<" si portul: "<<port<<std::endl;
    close (sd);
}

