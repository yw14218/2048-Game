#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

int twod_to_oned(int row, int col, int rowlenghth);
bool proc_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
void print_grid(const std::vector<int>& v);
bool game_over(const std::vector<int>& v);

void random_two_generation(std::vector<int>& v);
bool a_instruction(std::vector<int>& v);
bool w_instruction(std::vector<int>& v);
bool s_instruction(std::vector<int>& v);
bool d_instruction(std::vector<int>& v);

int main(){
    std::string filename;
    std::vector<int> v;
    std::string input;

    std::cout << "please enter name of file: " << std::endl;
    std::cin >> filename;
    std::ifstream infile;
    infile.open(filename.c_str());
    int tmp;
    while(infile >> tmp){
          v.push_back(tmp);
          /// Remember to close the file
    }
    //  read filename
    if(!infile.is_open()){
        std::cout << "file not found, using default start configuration" << std::endl;
        int r = 0;
        while(r++ < 15){
              v.push_back(0);
        }
        v.push_back(2);
    }
    print_grid(v);
    while(!game_over(v)){
          std::cout << std::endl;
          std::cout << std::endl;
          /// Could also just simplify to std::cout << std::endl << std::endl;
          std::cin >> input;
          std::cout << std::endl;
          std::cout << std::endl;
          if(input == "a"){
             if(a_instruction(v)){
                random_two_generation(v);
                print_grid(v);
             }
          }
          if(input == "d"){
             if(d_instruction(v)){
                random_two_generation(v);
                print_grid(v);
             }
          }
          if(input == "w"){
             if(w_instruction(v)){
                random_two_generation(v);
                print_grid(v);
             }
          }
          if(input == "s"){
             if(s_instruction(v)){
                random_two_generation(v);
                print_grid(v);
             }
          }
    }
    std::cout << "game over" << std::endl;
    return 0;
}


int twod_to_oned(int row, int col, int rowlenghth){
    return row*rowlenghth+col;
}

bool proc_num(std::vector<int>& v, int bi, int ei){
     std::vector<int> out;
     std::vector<int> tmp;
     std::vector<int> copy;
     for(int i = 0; i < bi; i++){
         int c = v[i];
         out.push_back(c);
     }
     for(int m = bi; m < ei; m++){
         if(v[m] != 0){
            int b = v[m];
            tmp.push_back(b);
         }
     }
     int trans;
     for(unsigned x = 0; x < tmp.size(); x++){
         int n1 = tmp[x];
         int n2 = tmp[x+1];
         if((x+1) >= tmp.size()){
           n2 = 0;
         }
         if((n1 == n2)){
            trans = n1 + n2;
            x = x + 1;
            out.push_back(trans);
         }
         else{
            trans = n1;
            out.push_back(trans);
         }
     }

     for(int y = out.size(); y < ei; y++){
         out.push_back(0);
     }
     for(unsigned z = ei; z < v.size(); z++){
         int k = v[z];
         out.push_back(k);
     }
     for(unsigned b = 0; b < v.size(); b++){
         copy.push_back(v[b]);
         }
     for(unsigned s = 0; s < v.size(); s++){
         v[s] = out[s];
         }
     for(unsigned c = 0; c < v.size(); c++){
         if(copy[c] != out[c]){
            return true;
         }
      }
     return false;
}

void rotate_anti_clock(std::vector<int>& v){
     int lenghth = sqrt(v.size());
     std::vector<int> tmp;
     for(int row = lenghth - 1; row >= 0; --row){
         for(int col = lenghth - 1 ; col >= 0; --col){
             int anti_col = row;
             int anti_row = lenghth - 1 - col;
             int coordinate = twod_to_oned(anti_row, anti_col, lenghth);
             int tempo = v[coordinate];
             tmp.push_back(tempo);
         }
      }
      for(unsigned i = 0; i < tmp.size(); i++){
          v[i] = tmp[i];
      }
}

  void print_grid(const std::vector<int>& v){
       unsigned lenghth = sqrt(v.size());
       for(unsigned x = 0; x < lenghth; x++){
           for(unsigned y = 0; y < lenghth; y++){
               int coordinate = twod_to_oned(x,y,lenghth);
               if(v[coordinate] < 10){
                  std::cout << v[coordinate] << "              ";
                  /// Would be simpler to use "\t"
               }
               if(v[coordinate] > 10 && v[coordinate] < 100){
                  std::cout << v[coordinate] << "             ";
               }
               if(v[coordinate] > 100 && v[coordinate] < 1000){
                  std::cout << v[coordinate] << "            ";
               }
               if(v[coordinate] > 1000 && v[coordinate] < 10000){
                  std::cout << v[coordinate] << "           ";
               }
               if(v[coordinate]> 10000 && v[coordinate] < 100000){
                  std::cout << v[coordinate] << "          ";
               }
               if(v[coordinate] > 100000 && v[coordinate] < 1000000){
                  std::cout << v[coordinate] << "         ";
               }
           }
           std::cout << std::endl;
       }
}

bool game_over(const std::vector<int>& v){
     unsigned lenghth = sqrt(v.size());
     std::vector<int> hold;
     std::vector<int> v_copy;
     for(unsigned i = 0; i < v.size(); i++){
         v_copy.push_back(v[i]);
     }
     int n = 0;
     while (n < 4){
        for(unsigned row = 0; row < lenghth; row++){
            for(unsigned col = 0; col < lenghth; col++){
                int coordinate = twod_to_oned(row, col, lenghth);
                hold.push_back(v_copy[coordinate]);
            }
            if(proc_num(hold, 0, lenghth)){
               return false;
               /// It would be better not to rely on the side effect of a function
               /// meant to change state to check if a property is true
            }
            hold.clear();
         }
         rotate_anti_clock(v_copy);
         n++;
     }
     return true;
}

void random_two_generation(std::vector<int>& v){
     srand((int)time(0));
     /// You should seed only once, in main, not each time you generate
     /// Otherwise you would get the same number if called in a short time span
     int r = rand() % v.size();
     while(v[r] != 0){
       /// If there is only one space with 0, you could be re-doing this a lot,
       /// would be better to filter to spaces with 0 first and randomly choose
       /// from them
           r = rand() % v.size();
     }
     v[r] = 2;

}

bool a_instruction(std::vector<int>& v){
     unsigned lenghth = sqrt(v.size());
     std::vector<int> hold;
     std::vector<int> v_copy;
     bool change = false;
     for(unsigned i = 0; i < v.size(); i++){
         v_copy.push_back(v[i]);
     }
     v.clear();
     for(unsigned row = 0; row < lenghth; row++){
         for(unsigned col = 0; col < lenghth; col++){
             int coordinate = twod_to_oned(row, col, lenghth);
             hold.push_back(v_copy[coordinate]);
         }
         if(proc_num(hold, 0, lenghth)){
            change = true;
         }
         for(unsigned r = 0; r < hold.size(); r++){
             int tmp = hold[r];
             v.push_back(tmp);
         }
         hold.clear();
      }
      return change;
}

bool  w_instruction(std::vector<int>& v){
      bool change;
      rotate_anti_clock(v);
      change = a_instruction(v);
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      if(change){
         return true;
      }
      else{
          return false;
      }

}

bool  s_instruction(std::vector<int>& v){
      bool change;
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      change = a_instruction(v);
      rotate_anti_clock(v);
      if(change){
         return true;
      }
      else{
          return false;
      }
}

bool d_instruction(std::vector<int>& v){
     bool change;
     rotate_anti_clock(v);
     change = w_instruction(v);
     rotate_anti_clock(v);
     rotate_anti_clock(v);
     rotate_anti_clock(v);
     if(change){
        return true;
     }
     else{
         return false;
     }
}
