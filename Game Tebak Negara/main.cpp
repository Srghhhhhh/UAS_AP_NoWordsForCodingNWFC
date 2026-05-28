#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

vector<string> negara = {"indonesia", "malaysia", "singapore", "brunei", "cambodia", "philippines", "thailand", "laos", "myanmar", "vietnam", "japan", "korea", "china", "india", "nepal", "bhutan", "bangladesh", "afghanistan", "pakistan", "jordan", "lebanon", "iraq", "iran", "iraq", "turkey", "greece", "italy", "spain", "france", "germany", "netherlands", "belgium", "switzerland", "austria", "denmark", "norway", "sweden", "finland", "russia", "ukraine", "poland", "hungary", "romania", "bulgaria", "serbia", "croatia", "slovenia", "slovakia", "albania", "macedonia", "montenegro", "kosovo", "estonia", "latvia", "lithuania", "belarus", "georgia", "armenia", "azerbaijan", "argentina", "brazil", "chile", "colombia", "ecuador", "paraguay", "peru", "uruguay", "venezuela", "bolivia", "guatemala", "honduras", "panama", "canada", "usa", "mexico", "cuba", "jamaica", "haiti", "bahamas", "barbados",  "grenada", "dominica", "antigua", "barbuda", "trinidad", "tobago", "belize", "nicaragua", "costarica", "haiti", "australia",  "fiji", "samoa", "tonga", "vanuatu", "kiribati", "palau", "rwanda", "uganda", "kenya", "tanzania", "ethiopia", "somalia", "sudan", "egypt", "libya", "tunisia", "algeria", "morocco", "mauritania", "mali", "niger", "chad", "cameroon", "ghana", "nigeria", "benin", "burkinafaso"};
string randomNegara (){
    int random = rand() % negara.size();
    return negara[random];
}

string hilanghuruf (string kunci){
    int n = kunci.length()/2;
    int count = 0;

    while (count < n) {
        int random = rand() % kunci.length();
        
        if (kunci[random] != '_') {
            kunci[random] = '_';
            count++;
        }
    }
    return kunci;
}

void cekjawaban (string jawaban, string kunci){
    if (jawaban == kunci){
        cout << "Selamat! Anda benar!" << endl;
    } else {
        cout << "Maaf jawaban anda salah. Coba lagi!" << endl;
    }
}

int cekskor (string jawaban, string kunci, int skor){;
    if (jawaban == kunci){
        skor += 1;
    }
    return skor;
}

int main (){
    srand(time(0));
    system ("cls");
    string start = "y";
    string jawaban;
    int skor = 0;

    while (start =="y"){
        string kunci = randomNegara();
        string tebakan = hilanghuruf(kunci);

        cout << "Tebak negara: " << tebakan << endl;
        cout << "Negara apakah yang dimaksud? "; cin >> jawaban;

        cekjawaban(jawaban, kunci);
        skor = cekskor(jawaban, kunci, skor);
        cout << "Skor anda: " << skor << endl;

        cout << "Ingin bermain lagi? (y/n) "; cin >> start;
        cout << endl;
        
    }
    cout << "Game Selesai :D" << endl;
}