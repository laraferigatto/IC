#include <bits/stdc++.h>
using namespace std;

// Número de indivíduos em cada geração
#define POPULATION_SIZE 100

// Genes Válidos
double GENES = 49.0; // população, P

// Alvo a ser gerado
double TARGET = 117.926; //  vzão -19,9275
// ramdom o vzinho até chegar no Vzão que eu quero

// Função para gerar números aleatórios em determinado intervalo
double random_num(int start, int end)
{
    int range = (end-start)+1;
    double random_int = start+(rand()%range);
    return random_int;
}

// Crie genes aleatórios para mutação
double mutated_genes()
{
    double r = 1.0/(double)(1+(1.0/(double)(rand()+1)));;
    r = r + (rand()%10);
    //cout << r << endl;
    return r;
}

// criar cromossomo ou cadeia de genes
double create_gnome() //gerou Vzão
{
    return  GENES*mutated_genes();

}

// Classe que representa o indivíduo na população
class Individual
{
public:
    double chromosome;
    double fitness;
    Individual(double chromosome);
    Individual mate(Individual parent2);
    double cal_fitness();
};

Individual::Individual(double chromosome)
{
    this->chromosome = chromosome;
    fitness = cal_fitness();
};

// Realize o acasalamento e produza novos descendentes
Individual Individual::mate(Individual par2)
{
    // cromossomo para prole
       double child_chromosome;



           // probabilidade aleatória
           float p = random_num(0, 100)/100;

           // se prob for menor que 0,45, insira o gene
           // pai 1
           if(p < 0.45)
           {
               double x = chromosome/GENES;
               child_chromosome = (x+1)*GENES;
           }

           // se prob estiver entre 0.45 e 0.90, insere
           // gene de pai 2
           else if(p < 0.90)
           {
               double x = par2.chromosome/GENES;
               child_chromosome = (x-0.1)*GENES;
           }

          // caso contrário, insira o gene aleatório (mutação),
          // para manter a diversidade
           else
           {
               //cout << "aqui\n";
               child_chromosome = mutated_genes();
           }


       // cria um novo indivíduo (prole) usando
       // cromossomo gerado para a prole
       return Individual(child_chromosome);
};


// Calcule a pontuação de aptidão
double Individual::cal_fitness()
{
    double fitness = 0;
    if(this->chromosome != TARGET)
        fitness = abs(chromosome - TARGET);

    return fitness;
};


bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}
int main()
{
    freopen("out", "w", stdout);
    srand((unsigned)(time(0)));

    // current generation
    int generation = 0;

    vector<Individual> population;
    // create initial population
    for(int i = 0;i<POPULATION_SIZE;i++)
    {
        double gnome = create_gnome();
        population.push_back(Individual(gnome));
    }

    while(true)
    {
        //classificar a população em ordem crescente de pontuação de aptidão
        sort(population.begin(), population.end());

        if((population[0].fitness) <= 0 or generation == 10)
        {
            break;
        }

        // Caso contrário, gere novos descendentes para a nova geração
        vector<Individual> new_generation;

        
        int s = (10*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++)
            new_generation.push_back(population[i]);

  
        s = (90*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++)
        {
            int len = population.size();
            int r = random_num(0, 50);
            Individual parent1 = population[r];
            r = random_num(0, 50);
            Individual parent2 = population[r];
            Individual offspring = parent1.mate(parent2);
            new_generation.push_back(offspring);
        }
        population = new_generation;
        cout<< "Geracao: " << generation << "\t";
        cout<< "V: "<< population[0].chromosome <<"\t";
        cout<< "Erro: "<< population[0].fitness << "\n";
        for(int i = 0; i < population.size(); i++)
        {
            cout<< "V; "<< population[i].chromosome <<" ;\t";
            cout<< "Erro; "<< population[i].fitness << "\n";
        }
        generation++;
    }
    cout<< "Geracao: " << generation << "\t";
    cout<< "V: "<< population[0].chromosome <<"\t";
    cout<< "Erro: "<< population[0].fitness << "\n";
    for(int i = 0; i < population.size(); i++)
    {
        cout<< "V; "<< population[i].chromosome <<" ;\t";
        cout<< "Erro; "<< population[i].fitness << "\n";
    }
}
