#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define advance(n)    ( ((n)>=3) ? ((n) = 0) : (++(n)) )
#define descend(n)    ( ((n)<=0) ? ((n) = 3) : (--(n)) )
#define isHeart(n)    (((n)>=1)  && ((n)<=13))
#define isSpade(n)    (((n)>=14) && ((n)<=26))
#define isDiamond(n)  (((n)>=27) && ((n)<=39))
#define isClub(n)     (((n)>=40) && ((n)<=52))

//players structure

typedef struct {
    char name[100];
    int cards[52]; // = {0};
    int card_count; // = 0;
} players;

/* initialize Card String */
    char *cardcontent[53] = {
                               "This_Will_Never_Be_Printed_:D",
                               "ONE HEARTS",
                               "TWO HEARTS",
                               "THREE HEARTS",
                               "FOUR HEARTS",
                               "FIVE HEARTS",
                               "SIX HEARTS",
                               "SEVEN HEARTS",
                               "EIGHT HEARTS",
                               "NINE HEARTS",
                               "TEN HEARTS",
                               "JACK HEARTS",
                               "QUEEN HEARTS",
                               "KING HEARTS",
                               "ONE SPADE",
                               "TWO SPADE",
                               "THREE SPADE",
                               "FOUR SPADE",
                               "FIVE SPADE",
                               "SIX SPADE",
                               "SEVEN SPADE",
                               "EIGHT SPADE",
                               "NINE SPADE",
                               "TEN SPADE",
                               "JACK SPADE",
                               "QUEEN SPADE",
                               "KING SPADE",
                               "ONE DIAMOND",
                               "TWO DIAMOND",
                               "THREE DIAMOND",
                               "FOUR DIAMOND",
                               "FIVE DIAMOND",
                               "SIX DIAMOND",
                               "SEVEN DIAMOND",
                               "EIGHT DIAMOND",
                               "NINE DIAMOND",
                               "TEN DIAMOND",
                               "JACK DIAMOND",
                               "QUEEN DIAMOND",
                               "KING DIAMOND",
                               "ONE CLUB",
                               "TWO CLUB",
                               "THREE CLUB",
                               "FOUR CLUB",
                               "FIVE CLUB",
                               "SIX CLUB",
                               "SEVEN CLUB",
                               "EIGHT CLUB",
                               "NINE CLUB",
                               "TEN CLUB",
                               "JACK CLUB",
                               "QUEEN CLUB",
                               "KING CLUB" };
//This has one-to-one mapping with cardcontents;
    char* errors[] = {
                     "The Game is Started with Ace Of Spades",
                     "You cannot throw a different color",
                     };
int cards[52] = {0};
players player_grp[] = {{"",{0},0},{"",{0},0},{"",{0},0},{"",{0},0}};
// ^ max 4 players
//one hand can have maximum of 4 cards
int currenthand[4][2]= {{0}}; //First is card, and second is userid
int deck_card_count = 0; //total card count in a deck, not necessarily needed/
int playerOrder[4] = {0,1,2,3}; //default order
int currentPlayer = 0; // current player
int currentMove = 1;  //current time of move [1-4]
int gameplaymoves = 0; //no. of moves in the gameplay
int carry = 0; //0 means no, 1 means yes; Set that in ai_play or user_play;

int printCenter(char* str) {printf("\n\t\t\t %s", str);return 0;}
int printNewLine(int n) { int i; for(i=0; i<n; i++) printf("\n"); return 0; }

int card_color(int card_id){
    if(isHeart(cards[card_id])){
        return 1;
    }
    else if(isSpade(cards[card_id])){
        return 2;
    }
    else if(isDiamond(cards[card_id])){
        return 3;
    }
    else{
        return 4;
    }
}

int flush_cards()
{
    int i = 0, n=52, temp_rand; time_t t;   char ch;
    int tab_mk= 0;
    start: ;
    //Re-initialize:
    reinit_card();
    i = 0; n =52;
    system("cls");

   srand((unsigned) time(&t));
   /* Print 53 unique random numbers from 0 to 52 */
    do{
      temp_rand = rand() % 53;
      if(tab_mk > 2 )
      {
          //printf("\n");
          tab_mk = 0;
      }
      if(is_unique(temp_rand))
      {
          //printf("%s\t", cardcontent[temp_rand]);
          cards[i] = temp_rand;
          i++;
          tab_mk++;

      }

   }while(i<=51);

   return 0;
}

int cards_sort(int arr[], int n){ //n= total_number_of_cards
    int i, j, tmp;
    for(i=0; i<n-1;i++){
        for(j=i+1; j<n; j++){
            if(arr[i]<arr[j]){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return 0;
}


int is_unique(int cur_rand){int j= 0;int flag = 1;for(j=0; j<=51; j++){if(cards[j] == cur_rand ){flag = 0;}}return flag;}
int reinit_card(){int i;for(i=0; i<=51; i++)cards[i] = 0;return 0;}
int sort_users_cards() {cards_sort(player_grp[0].cards, player_grp[0].card_count);return 0;}

//This supposedly means: to assign card from deck to the player.
//A Feature not necessarily needed on this thingo.
int give_card_first(int player_id){
    player_grp[player_id].cards[++(player_grp[player_id].card_count)] = cards[52 - deck_card_count];
    deck_card_count++;
    return 0;
}


int give_hand(int player_id)
{
    //loop and assign hand to player
}

int assign_cards() {
//loop
//assign card in round order;
    int i;
    int c_count = 0;
    for(i=0; i<49; i+=4){
            player_grp[0].cards[c_count] = cards[51-i];
            //printf("%d \n", cards[51-i]);
            player_grp[0].card_count ++;
            player_grp[1].cards[c_count] = cards[51-(i+1)];
            player_grp[1].card_count ++;
            player_grp[2].cards[c_count] = cards[51-(i+2)];
            player_grp[2].card_count ++;
            player_grp[3].cards[c_count] = cards[51-(i+3)];
            player_grp[3].card_count ++;
            c_count++;
    }
    return 0 ;
}


int init_players() {
    //prompt for usernames and store in structure
    int i;
    system("cls");
    printCenter("Initialize Players\n\nNote that Player One is User\n");
    for(i=0; i<=3; i++){
        printf("Enter Player %d 's Name: ", i+1);
        gets(player_grp[i].name);
        printNewLine(1); //prints 1 new lines
    }

    return 0;
}

int checkForAceSpade(){
//never call it before init_game();
//iterate through all the players card, until you find ace of spades..
//returns player id
    int i, j;
    for(i=0; i<=3; i++){
        for(j=0; j<=12; j++){
            if(player_grp[i].cards[j] == 14 )
            return i;
        }
    }
    //if Ace of spade is not found, error is occured.
    return -99;
}

int assign_PlayerOrder() {
    int i, PlayerToStart, n;
    n = PlayerToStart = checkForAceSpade();
    playerOrder[0] = PlayerToStart;
    for(i=1; i<4; i++){
        playerOrder[i] = (n >= 3) ?  n = 0  : ++n ;
    }

    currentPlayer = PlayerToStart;
/* For Debug

    for(i=0; i<4; i++) {
        printf("%d\n", playerOrder[i]);
       }
*/
    return 0;

}


int print_user_cards(){
//user is always player 1
    int i;
    for(i=0; i<player_grp[0].card_count; i++) {
        printf("Card No: %d ::", i+1);
        puts(cardcontent[player_grp[0].cards[i]]);
        printNewLine(1);
    }

}

int verifyMove(int card_id, int* error_id)
{
    int hold_player, hold_move;
    if(gameplaymoves == 0)
    {
        if(cards[card_id]!=14)
        {
            *error_id = 0;
            return 0; //false
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if(currentMove == 1){
            //this is the first move, user is allowed to throw anything
            return 1;
        }
        else
        {
            hold_player = currentPlayer;
            hold_move = currentMove;
            descend(hold_player);
            descend(hold_move);
            switch (card_color(currenthand[hold_move][1]))
            {
                case 1:
                if(isHeart(cards[card_id])) return 1; break;

                case 2:
                if(isSpade(cards[card_id])) return 1; break;

                case 3:
                if(isDiamond(cards[card_id])) return 1; break;

                case 4:
                if(isClub(cards[card_id])) return 1; break;

                default:
                *error_id = 1;
                return 0; break;
            }
        }
    }
}

int checkForSimilarColor(int card_id){
    int hold_move = currentMove;

}

int card_id_from_value(int value, int checkarr[], int n){
    int i;
    for(i=0; i<n; i++){
        if(checkarr[i]==14) return i;
    }
    return -99;
}

int ai_play(int player_id){
    //AI Play
    int PrevCard, HighestCardInHand, throw_id;
    int hold_move = currentMove;
    if(currentMove==1){
        currenthand[currentMove][0] = player_id; //player id
        currenthand[currentMove][1] = 14;
        player_grp[player_id].cards[card_id_from_value(14,
        player_grp[player_id].cards,player_grp[player_id].card_count)] = 0;
        player_grp[player_id].card_count--;
        return 0;
    }
    else
    {
        descend(hold_move);
        PrevCard = currenthand[hold_move][1];
        if(colorexists(PrevCard, player_grp[player_id].cards, player_grp[player_id].card_count)) {
            HighestCardInHand = get1maxfrom2d(currenthand,player_grp[player_id].card_count);
            throw_id =  gethighLowerthan(player_grp[player_id].cards, HighestCardInHand, player_grp[player_id].card_count);
            currenthand[currentMove][0] = player_id; //player id
            currenthand[currentMove][1] = player_grp[player_id].cards[throw_id];
            player_grp[player_id].cards[throw_id] = 0;
            player_grp[player_id].card_count--;
        }


    }
}
int colorexists(int card_id, int card_list[], int max_cards){
    int i;
    for(i=0; i<max_cards; i++){
        if(card_list[i]==card_id) return 1;
    }
    return 0;
}

int get1maxfrom2d(int arr[][2],int max){
    int i, m;
    for(i=0; i<max-1; i++){
        if(arr[i][1]>arr[i+1][1]){
            m = arr[i][1];
        }
        else {
            m = arr[i+1][1];
        }
    }
    return m;
}

int gethighLowerthan(int list[], int upper, int list_max){
    int i, mx= 0 ;
    for(i=0; i<list_max; i++){
        if((list[i]<upper) && (comparecolor(list[i], upper)) && list[i]>mx ){
            mx = list[i];
        }
    }
    return mx;
}
int comparecolor(int card_1, int card_2){
    switch(card_color(card_1)){

    case 1:
    if(isHeart(card_2)) return 1;
    break;

    case 2:
    if(isSpade(card_2)) return 1;
    break;

    case 3:
    if(isDiamond(card_2)) return 1;
    break;

    case 4:
    if(isClub(card_2)) return 1;
    break;

    default:
    return 0;

    }
    return 0;
}

int user_play(){
    //prompt for user to play
    int errorid= 99; //no error;
    int user_move;
    usr_str: ;
    printNewLine(2);
    printf("Please Enter Which card do you want to play: ");
    scanf("%d", &user_move);
    if(user_move<=0 || user_move > player_grp[0].card_count){
        printf("\nError! Please Enter Appropriate card number!");
        printf("\nEnter Any key to continue");
        getch();
        system("cls");
        print_user_cards();
        goto usr_str;
    }
    user_move--;
    if(verifyMove(player_grp[0].cards[user_move], &errorid)){
            currenthand[currentMove][0] = 0; //player id
            currenthand[currentMove][1] = player_grp[0].cards[user_move];
            player_grp[0].cards[user_move] = 0;
            sort_users_cards();
            player_grp[0].card_count--; //first sort, and remove the last.
            if(checkForSimilarColor(currenthand[currentMove][1])) {
                carry = 0;
            } else {
                carry =1;
            }
            return 0;
    }
    else {
        printf("\nError! : ");
        puts(errors[errorid]);
        printf("\nEnter Any key to continue");
        getch();
        system("cls");
        print_user_cards();
        goto usr_str;

    }

}

int gameplay(){
    // call corresponding funciton
    //call advance(currentPlayer); at last
    //infinite loop
    while(1){
        printf("GameplayMoves: %d \n", gameplaymoves);
        if(currentPlayer==0){
            user_play();
            gameplaymoves++;
        }
        else{
            ai_play(currentPlayer);
            gameplaymoves++;
        }
        //After each move, check if someone has to carry or not!
        if(carry) { CheckCarryAndAssign(); }
        if(currentMove == 4){
            //this is last move;
            setCurrentPlayer();
        } else {
            advance(currentPlayer);
            advance(currentMove);
        }
    }
}

int CheckCarryAndAssign() {
    //run a loop on current hands.
    //if someone has
    int i, to_carry_id;
    int currentCards;
    for(i=0;i<currentMove-1; i++){
        if(currenthand[i][1]>currenthand[i+1][1]) {
                to_carry_id = currenthand[i][0];
        }
        else
        {
            to_carry_id = currenthand[i+1][0];
        }
    }
    //Now loop and make the person carry
    currentCards = player_grp[to_carry_id].card_count;
    for(i=currentCards - 1 ; i<(currentCards + currentMove -1); i++){
        player_grp[to_carry_id].cards[i] = currenthand[i- currentCards +1][1] ;
        player_grp[to_carry_id].card_count++;
    }

    //also set the same player should start the game
    currentPlayer = to_carry_id;
}

int setCurrentPlayer(){
    int i, to_start_id;
    for(i=0;i<currentMove-1; i++){
        if(currenthand[i][1]>currenthand[i+1][1]) {
                to_start_id = currenthand[i][0];
        }
        else
        {
            to_start_id = currenthand[i+1][0];
        }
    }
    currentPlayer =to_start_id;
}

int play(){
    //the play logic.
    //Player who has Ace of Spade Starts the game
    assign_PlayerOrder();
    sort_users_cards();
    print_user_cards();
    gameplay();
    exit(123);
return 0;
}

int init_game() {reinit_card();flush_cards(); flush_cards();return 0;}


int main(){
    init_players();
    init_game();
    assign_cards();
    play(); //incomplete
    return 0;
}
