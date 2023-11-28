#include "geesespotter_lib.h"
#include <iostream>

    int min_loc ();//min helper function
    int max_loc ();//max helper function
    int *index_to_cord(int index, int col);

    int min_loc(std::size_t &num1, std::size_t num2){ //helper function to determine the smaller value when comparing x_loc or y_loc with respective dim variable

      if (num1>num2){
          return num2;
      
      } else {
        return num1; // returns smaller num
      } 

    }

    int max_loc(std::size_t &num1, std::size_t num2){ //helper function to determine the greater value when comparing x_loc or y_loc with respective dim variabl

      if (num1>num2){
          return num1;
      
      } else {
        return num2; // returns greater num
      } 

    }

    int *index_to_cord(int index, int col){ // converts an index to coordinates

      int* array = new int [2];
      array[0] = index%col;
      array[1] = index/col;

      return array;

    }

    char * create_board(std::size_t x_dim, std::size_t y_dim) { //Allocates a char array with size (x_dim * y_dim) and fills it with the value 0.
    std::size_t n {x_dim*y_dim};  //n calculates size of board
    char* array = new char [n];  //
    
    for(std::size_t k{0}; k<n; ++k){
        array[k]=0;
    }
    
    return array; // double check this and see if its not just array?
    }
    
    void clean_board(char * board) { //Deallocate the given board
      delete [] board;
        board = nullptr; // delete the pointer (every pointer itself has memory)
    }

    void print_board(char * board, std::size_t x_dim, std::size_t y_dim) { //Prints out the board using M for marked tiles, * for hidden tiles, 9 for tiles containing a goose, otherwise the value is (1-8)

      for (std::size_t y{0}; y<y_dim; ++y) { //for loop to loop through every point/star of the board (for the y=> rows)

        for (std::size_t x{0}; x<x_dim; ++x) { //for loop to loop through every point/star of the board (for the x=> columns)

          char b_num = board[(y*x_dim) + x];

                
             if ((b_num & marked_mask())== marked_mask()) {

                std::cout<<"M";
                
                }
              
              else if ((b_num & hidden_mask())== hidden_mask()) { //checks if hidden - if statement
              
              std::cout<<'*';
                
                }

                  else {
                    std::cout<< (int) (b_num&value_mask()); //prints out the digit numbers

              }

              }
              std::cout<<std::endl;
          }

     }
  
    void hide_board (char * board, std::size_t x_dim, std::size_t y_dim) { //Hides the entire board

      for (std::size_t y{0}; y<y_dim; ++y) { 
        
        for (std::size_t x{0}; x<x_dim; ++x) { //for loop to looper through every point/star of the board (for the x=> columns)

         int hide_num = ((y*x_dim) + x); //check if this is int or char
         board[hide_num] |= hidden_mask(); 
         }

     }
     return;
    
    }

    int mark(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc) { //Toggles the marked state of the tile at (x=x_loc, y=y_loc) => if the tile is already revealed, does nothing and returns 2. Otherwise, return 0.

            //int mark_num = ((y_loc*x_dim) + x_loc); //check if this is int or char
            
            if ((x_loc>=x_dim) || (y_loc>=y_dim)) { // to check if it is in the bounds of the grid, so it returns an error
              return -1;
            }


            if ((board[(y_loc * x_dim) + x_loc] & hidden_mask())!= hidden_mask()) {
              return 2;

            }

              board[(y_loc * x_dim) + x_loc] ^= marked_mask();  
              return 0;

            }

     
    void compute_neighbours(char * board, std::size_t x_dim, std::size_t y_dim) { //Given a board with all the elements having value 9 (for a goose) and 0 (otherwise), updates the value of every non-goose tile to the number of adjacent geese.

          for (std::size_t y{0}; y<y_dim; ++y) { //for loop to loop through every point/star of the board (for the y=> rows)

              for (std::size_t x{0}; x<x_dim; ++x) {

                char current = board[(y*x_dim) + x];
                
                char geese_counter {0};

                if(current== 0b0001001) {
                  continue; //skips current condition
                }

                if (y==0) { 

                   if (x == 0) {
                      char bottom = board[(y+1)*x_dim+x];
                      char bottom_right = board[(y+1)*x_dim+(x+1)];
                      char right = board[(y)*x_dim+(x+1)];

                      if(bottom==9){
                        geese_counter++;
                      }

                      if(bottom_right==9) {
                        geese_counter++;
                      }   

                      if(right==9) {
                        geese_counter++;
                      }                

                   } else if (x == (x_dim-1)) {

                      char bottom = board[(y+1)*x_dim+x];
                      char bottom_left = board[(y+1)*x_dim+(x-1)];
                      char left = board[(y)*x_dim+(x-1)];

                      if(bottom==9){
                        geese_counter++;
                      }

                      if(bottom_left==9) {
                        geese_counter++;
                      }   

                      if(left==9) {
                        geese_counter++;
                      }                

                   } else {

                      char bottom = board[(y+1)*x_dim+x];
                      char bottom_right = board[(y+1)*x_dim+(x+1)];
                      char right = board[(y)*x_dim+(x+1)];
                      char bottom_left = board[(y+1)*x_dim+(x-1)];
                      char left = board[(y)*x_dim+(x-1)];

                      if(bottom==9){
                        geese_counter++;
                      }

                      if(bottom_right==9) {
                        geese_counter++;
                      }   

                      if(right==9) {
                        geese_counter++;
                      }            

                      if(bottom_left==9) {
                        geese_counter++;
                      }   

                      if(left==9) {
                        geese_counter++;
                      }      


                   }



                } else  if (y==(y_dim-1)) {

                   if (x == 0) {
                      char top = board[(y-1)*x_dim+x];
                      char top_right = board[(y-1)*x_dim+(x+1)];
                      char right = board[(y)*x_dim+(x+1)];

                      if(top==9){
                        geese_counter++;
                      }

                      if(top_right==9) {
                        geese_counter++;
                      }   

                      if(right==9) {
                        geese_counter++;
                      }                

                   } else if (x == (x_dim-1)) {

                      char top = board[(y-1)*x_dim+x];
                      char top_left = board[(y-1)*x_dim+(x-1)];
                      char left = board[(y)*x_dim+(x-1)];

                      if(top==9){
                        geese_counter++;
                      }

                      if(top_left==9) {
                        geese_counter++;
                      }   

                      if(left==9) {
                        geese_counter++;
                      }                

                   } else {

                      char top = board[(y-1)*x_dim+x];
                      char top_right = board[(y-1)*x_dim+(x+1)];
                      char right = board[(y)*x_dim+(x+1)];
                      char top_left = board[(y-1)*x_dim+(x-1)];
                      char left = board[(y)*x_dim+(x-1)];

                      if(top==9){
                        geese_counter++;
                      }

                      if(top_right==9) {
                        geese_counter++;
                      }   

                      if(right==9) {
                        geese_counter++;
                      }            

                      if(top_left==9) {
                        geese_counter++;
                      }   

                      if(left==9) {
                        geese_counter++;
                      }      
                   }
                
                } else{ //middle rows

                   if (x == 0) {
                      char top = board[(y-1)*x_dim+x];
                      char top_right = board[(y-1)*x_dim+(x+1)];
                      char right = board[(y)*x_dim+(x+1)];
                      char bottom_right = board[(y+1)*x_dim+(x+1)];
                      char bottom = board[(y+1)*x_dim+(x)];

                      if(top==9){
                        geese_counter++;
                      }

                      if(top_right==9) {
                        geese_counter++;
                      }   

                      if(right==9) {
                        geese_counter++;
                      } 

                      if(bottom_right==9) {
                        geese_counter++;
                      }   

                      if(bottom==9) {
                        geese_counter++;
                      }                

                   } else if (x == (x_dim-1)) {

                      char top = board[(y-1)*x_dim+x];
                      char top_left = board[(y-1)*x_dim+(x-1)];
                      char left = board[(y)*x_dim+(x-1)];
                      char bottom_left = board[(y+1)*x_dim+(x-1)];
                      char bottom = board[(y+1)*x_dim+(x)];

                      if(top==9){
                        geese_counter++;
                      }

                      if(top_left==9) {
                        geese_counter++;
                      }   

                      if(left==9) {
                        geese_counter++;
                      } 

                       if(bottom_left==9) {
                        geese_counter++;
                      }   

                      if(bottom==9) {
                        geese_counter++;
                      }                

                   } else {

                      char top = board[(y-1)*x_dim+x];
                      char top_right = board[(y-1)*x_dim+(x+1)];
                      char right = board[(y)*x_dim+(x+1)];
                      char top_left = board[(y-1)*x_dim+(x-1)];
                      char left = board[(y)*x_dim+(x-1)];
                      char bottom_right = board[(y+1)*x_dim+(x+1)];
                      char bottom_left = board[(y+1)*x_dim+(x-1)];
                      char bottom = board[(y+1)*x_dim+(x)];


                      if(top==9){
                        geese_counter++;
                      }

                      if(top_right==9) {
                        geese_counter++;
                      }   

                      if(right==9) {
                        geese_counter++;
                      }            

                      if(top_left==9) {
                        geese_counter++;
                      }   

                      if(left==9) {
                        geese_counter++;
                      }      

                      if(bottom_right==9) {
                        geese_counter++;
                      }            

                      if(bottom_left==9) {
                        geese_counter++;
                      }   

                      if(bottom==9) {
                        geese_counter++;       

                   }
                }

            }  board[(y*x_dim) + x] = int(geese_counter);
          } 
      }
    }
   
    bool is_game_won(char * board, std::size_t x_dim, std::size_t y_dim) { //Returns whether the game is won (ex. all non-goose tiles have been revealed)
      
        for (std::size_t i {0}; i < x_dim*y_dim; i++ ) {
          if(((board[i]&value_mask())!=9)  && ((board[i]&hidden_mask()) != 0)) {
            return false;
          }
        }   
        return true;  
    }

    int reveal(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc) { // Attemps to reveal the tile at (x=x_loc, y=y_loc) => If the tile revealed had a value 0, additionally reveals 8 adjacent tiles => if tile is marked, returns without modifying board. => If tile is already revealed, returns 2. => Otherwise, returns 0. 
    std::size_t value{ 0 };

      if ((board[(y_loc * x_dim) + x_loc] & marked_mask()) == marked_mask()) { // if it's marked
        return 1;

      }
      else if ((board[(y_loc * x_dim) + x_loc] & hidden_mask()) != hidden_mask()) {//if no hidden
        return 2;

      }
      else if ((board[(y_loc * x_dim) + x_loc] & value_mask()) == 9) { //CHECK IF ITS HIDDEN OR NOT FIRST
        board[(y_loc * x_dim) + x_loc] ^= hidden_mask(); //reveal the number
        return 9;

      }
      else if (((board[(y_loc * x_dim) + x_loc] & hidden_mask()) == hidden_mask()) && ((board[(y_loc * x_dim) + x_loc] & value_mask()) != 0)) {
        board[(y_loc * x_dim) + x_loc] ^= hidden_mask(); //reveal the number

        return 0;

      }
      else if (((board[(y_loc * x_dim) + x_loc] & hidden_mask()) == hidden_mask()) && ((board[(y_loc * x_dim) + x_loc] & value_mask()) == 0)) {

        board[(y_loc * x_dim) + x_loc] ^= hidden_mask();

        if (y_loc >= 1) {
          int y = y_loc - 1;
          int x = x_loc;
          char top = board[(y * x_dim) + x];
          if (((top & hidden_mask()) == hidden_mask()) && ((top & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[(y * x_dim) + x] ^= hidden_mask(); //reveal it
          }
        }

        if (y_loc >= 1 && x_loc >= 1) {
          int y = y_loc - 1;
          int x = x_loc - 1;
          char top_left = board[(y * x_dim) + x];
          if (((top_left & hidden_mask()) == hidden_mask()) && ((top_left & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[(y * x_dim) + x] ^= hidden_mask(); //reveal it
          }
        }

        if (y_loc >= 1 && x_loc + 1 < x_dim) {
          int y = y_loc - 1;
          int x = x_loc + 1;
          char top_right = board[(y * x_dim) + x];
          if (((top_right & hidden_mask()) == hidden_mask()) && ((top_right & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[(y * x_dim) + x] ^= hidden_mask(); //reveal it
          }
        }

        if (x_loc >= 1) {
          int y = y_loc;
          int x = x_loc - 1;
          char left = board[(y * x_dim) + x];
          if (((left & hidden_mask()) == hidden_mask()) && ((left & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[y * x_dim + x] ^= hidden_mask(); //reveal it
          }
        }

        if (x_loc + 1 < x_dim) {
          int y = y_loc;
          int x = x_loc + 1;
          char right = board[(y * x_dim) + x];
          if (((right & hidden_mask()) == hidden_mask()) && ((right & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[y * x_dim + x] ^= hidden_mask(); //reveal it
          }
        }

        if (y_loc + 1 < y_dim) {
          int y = y_loc + 1;
          int x = x_loc;
          char bottom = board[(y * x_dim) + x];
          if (((bottom & hidden_mask()) == hidden_mask()) && ((bottom & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[y * x_dim + x] ^= hidden_mask(); //reveal it
          }
        }

        if (y_loc + 1 < y_dim && x_loc >= 1) {
          int y = y_loc + 1;
          int x = x_loc - 1;
          char bottom_left = board[(y * x_dim) + x];
          if (((bottom_left & hidden_mask()) == hidden_mask()) && ((bottom_left & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[y * x_dim + x] ^= hidden_mask(); //reveal it
          }
        }

        if (y_loc + 1 < y_dim && x_loc + 1 < x_dim) {
          int y = y_loc + 1;
          int x = x_loc + 1;
          char bottom_right = board[(y * x_dim) + x];
          if (((bottom_right & hidden_mask()) == hidden_mask()) && ((bottom_right & marked_mask()) != marked_mask())) { // if bottom is hidden and not marked
            board[(y * x_dim) + x] ^= hidden_mask(); //reveal it
          }
        }
      }



      return 0;
    }

