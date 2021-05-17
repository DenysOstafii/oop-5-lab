
//Створити базовий клас ПРОГНОЗ ПОГОДИ(задаються місце та дата).
//Створити похідні класи ПРОГНОЗ ЩОДО ВОДИ(задаються температура, швидкість хвилі) та 
//ПРОГНОЗ ЩОДО ОПАДІВ ТА ІН. (задаються наявність дощу / снігу / граду / грому та блискавок).Для введених даних про прогноз погоди визначити середню температуру води, дні з найвищою швидкістю хвилі, кількість днів з температурою води, вищою за середнє значення та кількість днів з прогнозованими опадами кожного із 2 - х заданих видів.
//Для перевірки використати масив вказівників на об’єкти базового класу, яким присвоїти адреси об’єктів похідних класів.
#include <iostream>
#include <string>
#include <cstring>
#define T 5

using namespace std;
int size;

class Weather
{
public:
    string place;
    string data;

public:
    Weather()
    { }
    Weather(string p, string d)
    {
        place = p;
        data = d;
    }
    ~Weather() {}
    void SetPlace(string p)
    {
        place = p;
    }

    void SetDate(string d)
    {
        data = d;
    }
    string GetPlace() { return place; }
    string GetDate() { return data; }
   
    virtual double GetTemp() { return 0; }
    virtual double GetWater() { return 0; }
    virtual double GetFall() { return 0; }
};

class Water : public Weather
{
private:
    double wave;
    double temp;
public:
    Water(string p, string d, double w, double t) : Weather(p,d), wave(w), temp(t)
    {}
    ~Water() {}
   void SetWater(double w)
    {
        wave = w;
    }

    void SetTemp(double t)
    {
        temp = t;
    }
    double GetWater() { return wave; }
    double GetTemp() { return temp; }
};

class Fallout : public Weather
{
private:
    double fall;
public:
    Fallout(double f) : Weather(), fall(f)
    { }

    ~Fallout() {}
    void SetFall(double f)
    {
        fall = f;
    }
    double GetFall()
    {
        return fall;
    }

};

void Average(double av, Weather* arr[]);
void WaveHighest(Weather* arr[]);
void FAll(Weather* arr[]);

int main()
{
    double sum=0, average;
    Weather *arr[T];
    int s, size=0;
    string d, p;
    double w, t,f;
    for (int i = 0; i < T; i++)
    {
        cout << "\nInput date : ";
        cin >> d;
        cout << "Input place : ";
        cin >> p;
        cout << "Input temp. of water : ";
        cin >> t;
        cout << "Input speed of wave : ";
        cin >> w;
        cout << "Input fallouts(rain - 1,snow - 2,thunder - 3,lightning - 4) : ";
        cin >> f;
        cout << "\n";
        arr[i] = new Water(p, d, w, t); 
        i++;
        arr[i] = new Fallout(f);
        sum += t;
    }
   average = sum / (3);
    cout << "\n\tAverage temp of water : " << average << endl;
    Average(average, arr);
   WaveHighest(arr);
   FAll(arr);
   delete[]arr;
    return 0;
}


void Average(double av, Weather* arr[])
{
    cout << "\n\tDay/s with the temp of water higher than average : \n\n";
    for (int r = 0; r<T; r++)
    {
        if (arr[r]->GetTemp() > av)
        {
            cout << arr[r]->GetPlace() << " " << arr[r]->GetDate() << " " << " Temp : " << arr[r]->GetTemp() << " Wave : " << arr[r]->GetWater() << "\n";
            r++;
            cout << "Fallouts : (rain - 1,snow - 2,thunder - 3,lightning - 4)  " << arr[r]->GetFall()<<"\n";
        }
        else
        {
            r++;
            continue;
        }
    }
}

void WaveHighest(Weather* arr[])
{
    int wave=0;
    int res = 0;
    for (int r = 0; r < T; r+=2)
    {
        if (arr[r]->GetWater() > res)
        {
            wave = r;
            res = arr[r]->GetWater();
        }
        else continue;
    }
    cout << "\n\n\tDay with the highets wave : \n\n";
    cout << arr[wave]->GetPlace() << " " << arr[wave]->GetDate() << " " << "  Temp : " << arr[wave]->GetTemp() << "  Wave : " << arr[wave]->GetWater() << "\n";
    cout << "Fallouts : (rain - 1,snow - 2,thunder - 3,lightning - 4)  " << arr[wave++]->GetFall()<<"\n\n";
}

void FAll(Weather* arr[])
{
    char line[T];
    int lich = 0, j=0, res=0;
    for (int r = 1; r < T+1; r+=2)
    {
        lich = arr[r]->GetFall();
        if (lich > 10)
        {
            res++;
        }
    }
    cout <<"\n"<<res << " :  days with more than 2 fallouts ";
}
