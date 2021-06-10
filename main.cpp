#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;


float generator(int n, int X, vector<float> &weight, vector<float> &value)
{
    value.clear();
    weight.clear();
    float W = X*(3.0/4.0);              //W - pojemność plecaka, X łączna waga przedmiotów

    float common_weight = (float)X / (float)n;

    for(int k = 0; k < n; k++)
    {
        weight.push_back(common_weight);
    }

    for(int i = 0; i < n; i++)
    {
        float g = rand() % 9;
        value.push_back(g);
    }

    return W;
}




vector<int> bruteForce(int n, float W, vector <int> A, vector<float> weight, vector<float> value)
{
    vector <int> bestChoice;
    float max_value = 0;

    float b = pow(n, 3);                                        //liczba 2^n - max liczba plecaków

    for(int i = 0; i < b; i++)
    {
        int j = n - 1;
        float temporary_weight = 0;
        float temporary_value = 0;


        while(A[j] !=0 && j > 0)                        //to w sprytny sposób zapewnia rosnącą zmianę bitów w tablicy A, z 000 na 001, z 001 na 010, z 010 na 011 itd.
        {
            A[j] = 0;
            j--;
        }
        A[j] = 1;


        for(int k = 0; k < n; k++)                  //tam gdzie bity sa równe 1 to sumujemy wagi i wartości ich odpowiedników w wektorach value i weight
        {
            if(A[k] == 1)
            {
                temporary_weight += weight[k];
                temporary_value += value[k];
            }
        }

        if((temporary_value > max_value) && (temporary_weight <= W))            //jeśli jest to najlepszy wynik do tej pory to zapisujemy go jako najlepszy wynik
        {
            max_value = temporary_value;

            bestChoice.clear();                         //czyszczenie wektora z poprzednich wartości
            for(int u = 0; u < n; u++)
            {
                bestChoice.push_back(A[u]);             //przypisanie wektora A do wektora bestChoice
            }
        }
    }

    return bestChoice;
}

int ns[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
int Xs[] = {30, 60, 90, 120, 150, 180, 210, 240, 270, 300};

int main()
{
    for(int i = 0; i < (sizeof(Xs) / sizeof(*Xs)); i++)
    {
        for(int j = 0; j < (sizeof(ns) / sizeof(*ns)); j++)
        {
            int n = ns[j];
            int X = Xs[i];

            vector<float> value;
            vector<float> weight;
            vector <int> A;
            for(int h = 0; h < n; h++)
            {
                A.push_back(0);
            }

            float W = generator(n, X, weight, value);



            clock_t begin = clock();
            vector<int> outcome = bruteForce(n, W, A, weight, value);
            clock_t end = clock();
            double seconds = (double)(end - begin) / (double)CLOCKS_PER_SEC;

            printf("Pojemność plecaka|liczba przedmiotów|czas_bruteForce|\t%.1f\t %d\t %lf\n", W, n, seconds);
            
        }
    }





}
