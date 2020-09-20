#include <iostream>
#include <set>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using std::set;

char board1[9][9];
int candidates[11]; 
int nums[11]; 
char board2[9][9];

set<int> memo_candidates;

/* =========================================== */

/*
*  THIS PART IS FOR SUDOKU_SOLVER!
*  SOLVE SUDOLU BY ALGORITHM-X
*  DANCING LINK SOLVER
*/

/* =========================================== */
const int MN = 9 * 9 * 9 + 10;
const int MM = 9 * 9 + 9 * 9 + 9 * 9 + 9 * 9 + 100;
const int MAX_NUM = MN * MM; 

char path[90];
char res[9][9];

struct DLX{
    int n, m, idx;

    int l[MAX_NUM], r[MAX_NUM], u[MAX_NUM], d[MAX_NUM]; 
    int col[MAX_NUM], row[MAX_NUM];


    int nodeIdxPerRow[MAX_NUM];        
    int nodeNumPerCol[MAX_NUM];        


    int ansd, ans[MN];

    void init(int n ,int m){
        for (int i = 0; i <= m; i++) {
            r[i] = i + 1;
            l[i] = i - 1;
            u[i] = d[i] = i;
        }
        r[m] = 0;
        l[0] = m;

        memset(nodeIdxPerRow, 0, sizeof(nodeIdxPerRow));
        memset(nodeNumPerCol, 0, sizeof(nodeNumPerCol));

        idx = m + 1;
    }

    void link(int insertRow, int insertCol){
        // printf("Linking %d -> %d\n", insertRow, insertCol);
        nodeNumPerCol[insertCol]++; 
        row[idx] = insertRow;
        col[idx] = insertCol; 

        u[idx] = insertCol;    
        d[idx] = d[insertCol];    
        u[d[insertCol]] = idx;    
        d[insertCol] = idx;       

       
        if (nodeIdxPerRow[insertRow] == 0) {
            nodeIdxPerRow[insertRow] = r[idx] = l[idx] = idx;
        }
        else {
            r[idx] = nodeIdxPerRow[insertRow];        
            l[idx] = l[nodeIdxPerRow[insertRow]];    
            r[l[nodeIdxPerRow[insertRow]]] = idx;   
            l[nodeIdxPerRow[insertRow]] = idx;

        }
        idx++;
        return;
    }

    void remove(int deleteCol) {
        r[l[deleteCol]] = r[deleteCol];
        l[r[deleteCol]] = l[deleteCol];
        for (int i = d[deleteCol]; i != deleteCol; i = d[i]) {
            for (int j = r[i]; j != i; j = r[j]) {
                u[d[j]] = u[j];
                d[u[j]] = d[j];
                nodeNumPerCol[col[j]]--;
            }
        }
    }

    void resume(int resCol) {
        for (int i = u[resCol]; i != resCol; i = u[i]) {
            for (int j = l[i]; j != i; j = l[j]) {
                u[d[j]] = j;
                d[u[j]] = j;
                nodeNumPerCol[col[j]]++;
            }
        }
        r[l[resCol]] = resCol;
        l[r[resCol]] = resCol;
    }



    bool dance(int deep) {
        if (r[0] == 0){
            ansd = deep;
            return 1;
        }


        int c = r[0];
        for (int i = r[0]; i != 0; i = r[i]){
            if (nodeNumPerCol[i] < nodeNumPerCol[c])
                c = i;
        }

        remove(c);
        for (int i = d[c]; i != c; i = d[i]){
            ans[deep] = row[i];
            for (int j = r[i]; j != i; j = r[j])
                remove(col[j]);
            if (dance(deep + 1))
                return 1;
            for (int j = l[i]; j != i; j = l[j])
                resume(col[j]);
        }
        resume(c);
        return 0;
    }
}dlx;

struct node{
    int r, c, v;
}nds[MN];

void print_res(){
    printf("The answer is: \n");
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            printf("%c", res[i][j]);
            if(j != 8)
                printf(", ");
        }
        printf("\n");
    }
}

int solve(){
    dlx.init(9 * 9 * 9, 9 * 9 * 4);
    int r = 1;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            if (board1[i - 1][j - 1] == '.')
            {
                for (int z = 1; z <= 9; z++)
                {
                    dlx.link(r, (i - 1) * 9 + j);
                    dlx.link(r, 81 + (i - 1) * 9 + z);
                    dlx.link(r, 162 + (j - 1) * 9 + z);
                    dlx.link(r, 243 + (((i - 1) / 3) * 3 + (j + 2) / 3 - 1) * 9 + z);
                    nds[r].r = i, nds[r].c = j, nds[r].v = z;
                    r++;
                }
            }
            else
            {
                int z = board1[i - 1][j - 1] - '0';
                dlx.link(r, (i - 1) * 9 + j);
                dlx.link(r, 81 + (i - 1) * 9 + z);
                dlx.link(r, 162 + (j - 1) * 9 + z);
                dlx.link(r, 243 + (((i - 1) / 3) * 3 + (j + 2) / 3 - 1) * 9 + z);
                nds[r].r = i, nds[r].c = j, nds[r].v = z;
                r++;
            }
        }
    }
        dlx.ansd = -1;
        dlx.dance(0);
        int deep = dlx.ansd;

        if(deep != 81){
            //printf("No solution!!!\n");
            return -1;
        }

        for (int i = 0; i < deep; i++){
            int posr = dlx.ans[i];
            path[(nds[posr].r - 1) * 9 + nds[posr].c - 1] = '0' + nds[posr].v;
            res[nds[posr].r - 1][nds[posr].c - 1] = '0' + nds[posr].v;
        }

        path[deep] = '\0';
        return 0;
}

/* =========================================== */

/*
*  THIS PART IS FOR SUDOKU_GENERATOR!
*
*
*/

/* =========================================== */

void copy_board(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            board2[i][j] = board1[i][j];
        }
    }
}

void reset_board(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            board1[i][j] = board2[i][j];
        }
    }
}

void test_rand_generator(){
    for (int i = 0; i < 11; ++i){
        printf("%d\t", candidates[i]);
        printf("%d\n", nums[i]);
    }
}

void clear_board(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            board1[i][j] = '.';
        }
    }
}

void print_board(){
    printf("The board is\n");
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            printf("%c", board1[i][j]);
            if(j != 8)
                printf(", ");
        }
        printf("\n");
    }
}

void get_nums(int nums[], const int N = 11){
    for (int i = 0; i < N; ++i){
        int x = rand() % 9;
        nums[i] = x + 1;
    }
}

void get_pos(int nums[], const int N = 11){
    int hash[82];
    int cur = 0;
    memset(hash, 0, sizeof(hash));

    while(1){
        int x = rand() % 81;
        if(cur == N){
            break;
        }

        if(hash[x] == 0){
            hash[x] = 1;
            nums[cur] = x;
            ++cur;
        }
        else{
            continue;
        }
    }
}

void generate_sudoku(){
    clear_board();
    srand(time(NULL));
    get_pos(candidates, 11);
    get_nums(nums, 11);

    for (int i = 0; i < 11; ++i){
        int nx = candidates[i] / 9, ny = candidates[i] % 9;
        board1[nx][ny] = '0' + nums[i];
    }
}

/* =========================================== */

/*
* After generate a possible sudoku, we would take one out
* and judge whether other number puts in the position
* would work out, too.
* If not, then we've already had it!
* Else, fix this num and try another one!
*/

/* =========================================== */

int unique_sudoku(){
    srand(time(NULL));
    int x = 0;

    while(true){
        x = rand() % 81;
        if(memo_candidates.find(x) == memo_candidates.cend()){
            break;
        }
    }

    int cur_x = x / 9, cur_y = x % 9;
    int cur_num = res[cur_x][cur_y] - '0';
    int cnt = 0;

    for (int k = 1; k <= 9; ++k){
        if(k == cur_num){
            continue;
        }
        else{
            board1[cur_x][cur_y] = '0' + k;
            if(solve() == 0){
                ++cnt;
            }
            board1[cur_x][cur_y] = '.';
        }
    }

    if(cnt == 0){
        board1[cur_x][cur_y] = cur_num + '0';
        return 1;
    }
    else{
        if(memo_candidates.size() >= 25){
            return 1;
        }
        else{
            board1[cur_x][cur_y] = cur_num + '0';
            memo_candidates.insert(x);
            return 0;
        }
    }
}

int main(){
    while(1){
        generate_sudoku();
        if(solve() == 0)
            break;
    }
    copy_board();

    for (int i = 0; i < 11; ++i){
        memo_candidates.insert(candidates[i]);
    }

    while(1){
        if(unique_sudoku() == 1){
            break;
        }
    }
    print_board();

    return 0;
}