#include <bits/stdc++.h>

using namespace std;
struct position
{
    int row;
    int col;
};

bool flip_bit(bool val)
{
    if (val == 1)
        val = 0;
    else
        val = 1;
    return val;
}

void print_1d_parity(bool a[], int n)
{
    for (int i = 0 ; i < n ; i++)
        cout << a[i] << " ";
    cout << "\n";
    return;
}

int main()
{

    int m, n, hv, d; // 8 8 3 4
    cin >> m >> n >>hv>> d;
    bool input[m][n];
    bool errored_matrix[m][n];
    bool r_xor, c_xor;
    vector < pair < bool, vector < pair <int, int> > > > row_parity_vector;
    vector < pair < bool, vector < pair <int, int> > > > col_parity_vector;
    bool col_parity[n];
    bool row_parity[m];

    srand((unsigned) time(0));
    cout<<"Input:"<<endl;

    for (int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            input[i][j] = rand() % 2;
            errored_matrix[i][j] = input[i][j];
            cout<<input[i][j]<<" ";
        }
        cout<<endl;
    }
    cout << endl;


    // row parity , d =3
    bool flag_row[m], flag_col[n];
    for(int i = 0 ; i < m ; i ++)
    {
        flag_row[i] = false;
        flag_col[i] = false;
    }

    int counter = 0;

    vector<bool> rp, cp;

    for (int i = 0 ; i < m ; i++)
    {
        if (flag_row[i] == true)
        {
            continue;
        }
        else if (flag_row[i] == false)
        {
            int nRowOnes = 0, nColOnes = 0;
            for (int k = i ; k < m ; k+=hv)
            {
                if (flag_row[k] == false)
                {
                    flag_row[k] = true;
                    for (int j = 0 ; j < n ; j++)
                    {
                        if(input[k][j])
                            ++nRowOnes;
                        if(input[j][k])
                            ++nColOnes;

                        //cout << "pos: " << k << " " << j << endl;
                        //cout << "pos: " << j << " " << k << endl;

                    }
                }
            }
            rp.push_back(nRowOnes%2);
            cp.push_back(nColOnes%2);
        }
    }

    cout << "row parity: \n";
    for (int i = 0; i < rp.size() ; i++)
    {
        cout << rp[i] << " " ;
    }
    cout << endl;
    cout << "col parity: \n";
    for (int i = 0; i < cp.size() ; i++)
    {
        cout << cp[i] << " " ;
    }


    /*
    for (int i = 0 ; i < m ; i++)
    {
        if (counter == 2*m - 1)
            break;
        if (flag_row[i] == true)
        {
            continue;
        }
        else if (flag_row[i] == false)
        {
            vector < pair <int, int> > temp_row;
            vector < pair <int, int> > temp_col;
            for (int k = i ; k < m ; k+=d)
            {

                if (flag_row[k] == false)
                {

                    flag_row[k] = true;
                    for (int j = 0 ; j < n ; j++)
                    {
                        temp_row.clear();
                        temp_col.clear();
                        if (j == 0)
                        {
                            r_xor = input[k][j];
                            temp_row.push_back(make_pair(k,j));
                        }
                        else
                        {
                            r_xor ^= input[k][j];
                            temp_row.push_back(make_pair(k,j));
                        }

                        if (k == 0)
                        {
                            c_xor = input[j][k];
                            temp_col.push_back(make_pair(j,k));
                        }
                        else
                        {
                            c_xor ^= input[j][k];
                            temp_col.push_back(make_pair(j,k));
                        }

                        //cout << "pos: " << k << " " << j << endl;
                        //cout << "pos: " << j << " " << k << endl;
                        ++counter;
                    }

                }
                row_parity_vector.push_back(make_pair(r_xor,temp_row));
                col_parity_vector.push_back(make_pair(c_xor,temp_col));
            }
        }
    }

    for (int i = 0 ; i < row_parity_vector.size() ; i++)
    {
        cout << row_parity_vector[i].first << endl;
    //        for (int j = 0 ; j < row_parity_vector[i].second.size() ; j++)
    //        {
    //            cout << row_parity_vector[i].second[j].first << " " <<  row_parity_vector[i].second[j].second << endl;
    //        }
    }

    */
    cout << endl;


    bool a[2*m-2];
    for (int i = 0 ; i <= 2*m-2 ; i++)
    {
        a[i] = false;
    }

    counter = 0;
    cout << "LEFT:\n";
    bool lp;
    vector <bool> ldp, rdp;

    for (int x = 0 ; x <= 2*m-2 ; x++)
    {
        if (counter >= 2*m - 1)
        {
            break;
        }
        if (a[x] == true)
        {
            continue;
        }
        if (a[x] == false)
        {
            int nOnes = 0;
            for (int i = x ; i <= 2*m-2 ; i+=d)
            {
                a[i] = true;
                //cout << i << " ";
                ++counter;

                if (i <= m-1)
                {
                    int row=i;
                    int col=0;

                    while (col < n && row >= 0)
                    {
                        if (input[row][col])
                            ++nOnes;
                        row--;
                        col++;
                        //cout << row-- << " " << col++;
                        //cout << endl;
                    }

                }

                else if (i > m-1)
                {
                    int col = i - (m-1);
                    int row = i - col;
                    if (input[row][col])
                    {
                        ++nOnes;
                    }

                    row--;
                    col++;
                    //cout << row-- << " " << col++;
                    a[row] = true;
                    //cout << endl;
                    while (row>=0 && col<n)
                    {
                        if (input[row][col])
                        {
                            ++nOnes;
                        }

                        row--;
                        col++;
                        //cout << row-- << " " << col++;
                        //cout << endl;
                    }
                }
            }
            //cout << "............. " << nOnes << endl;
            ldp.push_back(nOnes%2);
        }
    }
    cout << "Left diagonal parity: \n";
    for (int i = 0; i < ldp.size() ; i++)
    {
        cout << ldp[i] << " " ;
    }

    for (int i = 0 ; i <= 2*m-2 ; i++)
    {
        a[i] = false;
    }

    counter = 0;
    cout << "\nRIGHT: " << endl;

    vector  < pair < bool, pair <int,int>> >   flag_right_diag;
    int x;
    for (int i = 0 ; i < m ; i++)
    {
        flag_right_diag.push_back(make_pair(false, make_pair(i,n-1)));
        x = i;
    }
    for(int j = m-2 ; j >= 0 ; j--)
    {
        flag_right_diag.push_back(make_pair(false, make_pair(m-1,j)));
    }


    for (int x = 0 ; x <= 2*m-2 ; x++)
    {
        if (counter >= 2*m - 1)
        {
            break;
        }
        if (flag_right_diag[x].first == true)
        {
            continue;
        }
        if (flag_right_diag[x].first == false)
        {
            int nOnes = 0;
            for (int i = x ; i <= 2*m-2 ; i+=d)
            {
                if (flag_right_diag[i].first == false)
                {
                    flag_right_diag[i].first = true;
                    ++counter;
                    //cout << flag_left_diag[i].first << " " << flag_left_diag[i].second.first << " " << flag_left_diag[i].second.second << endl;

                    int row = flag_right_diag[i].second.first;
                    int col = flag_right_diag[i].second.second;
                    //cout << row<< " " << col << endl;
                    if (input[row][col])
                        ++nOnes;
                    row--;
                    col--;
                    while (col>=0 && row>=0)
                    {
                        //cout << row<< " " << col << endl;
                        if (input[row][col])
                        {
                            ++nOnes;
                        }
                        row--;
                        col--;
                    }
                }
                //cout << ".............. " << nOnes << endl;
            }
            //cout << ".............. " << nOnes << endl;
            rdp.push_back(nOnes%2);
        }
    }

    cout << "right diagonal parity: \n";
    for (int i = 0 ; i < rdp.size(); i++)
    {
        cout << rdp[i] << " ";
    }
    cout << endl;

    // error postion generation
    unordered_set<int> position_set;
    const int no_of_errored_positions = 1;
    const int total_pos = no_of_errored_positions*2;
    int positions[total_pos];
    while(position_set.size() <= total_pos-1)
    {
        position_set.insert(rand()%m); // 0 to m = 8
    }
    cout << "errored positions: ";
    unordered_set<int>::iterator itr;
    int i = 0;
    for(itr = position_set.begin(); itr!=position_set.end(); itr++)
    {
        positions[i++] = *itr;
    }
    cout << endl;

    // error injection
    for (int i = 0 ; i < total_pos ; i+=2)
    {
        int p1 = positions[i], p2 = positions[i+1];
        cout << p1 << " " << p2 << endl;
        errored_matrix[p1][p2] = flip_bit(errored_matrix[p1][p2]);
    }

    cout << "Errored matrix:\n";
    for (int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            cout << errored_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // errored row and col parity
    for(int i = 0 ; i < m ; i ++)
    {
        flag_row[i] = false;
        flag_col[i] = false;
    }

    counter = 0;

    vector<bool> erp, ecp;

    for (int i = 0 ; i < m ; i++)
    {
        if (flag_row[i] == true)
        {
            continue;
        }
        else if (flag_row[i] == false)
        {
            int nRowOnes = 0, nColOnes = 0;
            for (int k = i ; k < m ; k+=hv)
            {
                if (flag_row[k] == false)
                {
                    flag_row[k] = true;
                    for (int j = 0 ; j < n ; j++)
                    {
                        if(errored_matrix[k][j])
                            ++nRowOnes;
                        if(errored_matrix[j][k])
                            ++nColOnes;

                        //cout << "pos: " << k << " " << j << endl;
                        //cout << "pos: " << j << " " << k << endl;

                    }
                }
            }
            erp.push_back(nRowOnes%2);
            ecp.push_back(nColOnes%2);
        }
    }

    cout << "erroed row parity: \n";
    for (int i = 0; i < erp.size() ; i++)
    {
        cout << erp[i] << " " ;
    }
    cout << endl;
    cout << "errored col parity: \n";
    for (int i = 0; i < ecp.size() ; i++)
    {
        cout << ecp[i] << " " ;
    }
    cout << endl;

    // errored left

    for (int i = 0 ; i <= 2*m-2 ; i++)
    {
        a[i] = false;
    }

    counter = 0;
    cout << "Errored LEFT:\n";
    vector <bool> eldp, erdp;

    for (int x = 0 ; x <= 2*m-2 ; x++)
    {
        if (counter >= 2*m - 1)
        {
            break;
        }
        if (a[x] == true)
        {
            continue;
        }
        if (a[x] == false)
        {
            int nOnes = 0;
            for (int i = x ; i <= 2*m-2 ; i+=d)
            {
                a[i] = true;
                //cout << i << " ";
                ++counter;

                if (i <= m-1)
                {
                    int row=i;
                    int col=0;

                    while (col < n && row >= 0)
                    {
                        if (errored_matrix[row][col])
                            ++nOnes;
                        row--;
                        col++;
                        //cout << row-- << " " << col++;
                        //cout << endl;
                    }

                }

                else if (i > m-1)
                {
                    int col = i - (m-1);
                    int row = i - col;
                    if (errored_matrix[row][col])
                    {
                        ++nOnes;
                    }

                    row--;
                    col++;
                    //cout << row-- << " " << col++;
                    a[row] = true;
                    //cout << endl;
                    while (row>=0 && col<n)
                    {
                        if (errored_matrix[row][col])
                        {
                            ++nOnes;
                        }

                        row--;
                        col++;
                        //cout << row-- << " " << col++;
                        //cout << endl;
                    }
                }
            }
            //cout << "............. " << nOnes << endl;
            eldp.push_back(nOnes%2);
        }
    }
    cout << "Errored Left diagonal parity: \n";
    for (int i = 0; i < eldp.size() ; i++)
    {
        cout << eldp[i] << " " ;
    }
    cout << endl;


    // errored right diagonal parity

    for (int i = 0 ; i <= 2*m-2 ; i++)
    {
        a[i] = false;
    }

    counter = 0;
    cout << "Erroed RIGHT: " << endl;
    flag_right_diag.clear();
    for (int i = 0 ; i < m ; i++)
    {
        flag_right_diag.push_back(make_pair(false, make_pair(i,n-1)));
        x = i;
    }
    for(int j = m-2 ; j >= 0 ; j--)
    {
        flag_right_diag.push_back(make_pair(false, make_pair(m-1,j)));
    }


    for (int x = 0 ; x <= 2*m-2 ; x++)
    {
        if (counter >= 2*m - 1)
        {
            break;
        }
        if (flag_right_diag[x].first == true)
        {
            continue;
        }
        if (flag_right_diag[x].first == false)
        {
            int nOnes = 0;
            for (int i = x ; i <= 2*m-2 ; i+=d)
            {
                if (flag_right_diag[i].first == false)
                {
                    flag_right_diag[i].first = true;
                    ++counter;
                    //cout << flag_left_diag[i].first << " " << flag_left_diag[i].second.first << " " << flag_left_diag[i].second.second << endl;

                    int row = flag_right_diag[i].second.first;
                    int col = flag_right_diag[i].second.second;
                    //cout << row<< " " << col << endl;
                    if (errored_matrix[row][col])
                        ++nOnes;
                    row--;
                    col--;
                    while (col>=0 && row>=0)
                    {
                        //cout << row<< " " << col << endl;
                        if (errored_matrix[row][col])
                        {
                            ++nOnes;
                        }
                        row--;
                        col--;
                    }
                }
                //cout << ".............. " << nOnes << endl;
            }
            //cout << ".............. " << nOnes << endl;
            erdp.push_back(nOnes%2);
        }
    }

    cout << "Errored right diagonal parity: \n";
    for (int i = 0 ; i < erdp.size(); i++)
    {
        cout << erdp[i] << " ";
    }
    cout << endl;

    cout << "matching row parities: \n";
    vector < pair <int,int> > e_row_pos;
    for (int i = 0 ; i < rp.size() ; i++)
    {
        if (rp[i] != erp[i])
        {
            cout << i << endl;
            for (int x = i ; x < m ; x+=hv)
            {
                for (int y = 0 ; y < n ; y++)
                {
                    e_row_pos.push_back(make_pair(x,y));
                }
            }
        }
    }

//    cout << "erroed row pos:\n";
//    for (int i = 0 ; i < e_row_pos.size() ; i++)
//    {
//        cout << e_row_pos[i].first << " " << e_row_pos[i].second << endl;
//    }

    cout << "matching col parities: \n";
    vector < pair <int,int> > e_col_pos;
    for (int i = 0 ; i < cp.size() ; i++)
    {
        if (cp[i] != ecp[i])
        {
            cout << i << endl;
            for (int x = i ; x < n ; x+=hv
            )
            for (int x = i ; x < n ; x+=hv)
            {
                for (int y = 0 ; y < m ; y++)
                {
                    e_col_pos.push_back(make_pair(y,x));
                }
            }
        }
    }

//    cout << "erroed col pos:\n";
//    for (int i = 0 ; i < e_col_pos.size() ; i++)
//    {
//        cout << e_col_pos[i].first << " " << e_col_pos[i].second << endl;
//    }

    cout << "matching left diagonal parities: \n";
    vector < pair <int,int> > e_left_diag_pos;
    for (int x = 0 ; x < ldp.size() ; x++)
    {
        if (ldp[x] != eldp[x])
        {
            cout << "pos on edlp: " << x << endl;
            for (int i = x ; i <= 2*m-2 ; i+=d)
            {
                if (i==0) e_left_diag_pos.push_back(make_pair(0,0));
                else if (i <= m-1)
                {
                    int row=i;
                    int col=0;
                    e_left_diag_pos.push_back(make_pair(row--,col++));
                    while (col < n && row >= 0)
                    {
                        e_left_diag_pos.push_back(make_pair(row--,col++));

                    }

                }

                else if (i < 2*m-2)
                {
                    int row = m-1;
                    int col = i-m+1;
                    e_left_diag_pos.push_back(make_pair(row--,col++));
                    //cout << row << " " << col;
                    //cout << endl;

                    while (row>=0 && col<n)
                    {
                        e_left_diag_pos.push_back(make_pair(row--,col++));
                        //cout << row << " " << col;
                        //cout << endl;

                    }
                }
                else e_left_diag_pos.push_back(make_pair(m-1,n-1));
            }
        }
    }



    for (int i = 0 ; i < e_left_diag_pos.size() ; i++)
    {
        cout << e_left_diag_pos[i].first << " " << e_left_diag_pos[i].second << endl;
    }


    cout << "matching right diagonal parities: \n";
    vector < pair <int,int> > e_right_diag_pos;
    for (int z = 0 ; z < rdp.size() ; z++)
    {
        if (rdp[z] != erdp[z])
        {
            cout << "pos on erdp: " << z << endl;

            // print right diag pos
            for (int i = z ; i <= 2*m-2 ; i+=d)
            {
                if (i==0) e_right_diag_pos.push_back(make_pair(0,n-1));
                else if (i <= m-1)
                {
                    int row=i;
                    int col=n-1;
                    e_right_diag_pos.push_back(make_pair(row--,col--));
                    while (col >=0 && row >= 0)
                    {
                        e_right_diag_pos.push_back(make_pair(row--,col--));
                        //cout << row << " " << col;
                        //cout << endl;

                    }

                }

                else if (i < 2*m-2)
                {
                    int row=m-1;
                    int col=n-1-(i-m+1);
                    e_right_diag_pos.push_back(make_pair(row--,col--));
                    //cout << row << " " << col;
                    //cout << endl;
                    while (row>=0 && col>=0)
                    {
                        e_right_diag_pos.push_back(make_pair(row--,col--));
                        //cout << row << " " << col;
                        //cout << endl;

                    }
                }
                else e_right_diag_pos.push_back(make_pair(m-1,0));
            }
            //cout << endl;
        }

    }

    for (int i = 0 ; i < e_right_diag_pos.size() ; i++)
    {
        cout << e_right_diag_pos[i].first << " " << e_right_diag_pos[i].second << endl;
    }

    //error correction

    //candidate bits
    vector<pair<int,int>> candidate_bit;

    //row and col
    for (int i=0;i<e_row_pos.size();i++)
    {
        for (int j=0;j<e_col_pos.size();j++)
        {
            if ((e_row_pos[i].first==e_col_pos[j].first) && (e_row_pos[i].second==e_col_pos[j].second))
            {
                candidate_bit.push_back(e_row_pos[i]);
                break;
            }
        }
    }
    cout<<"candidate bits:"<<endl;
    for (int i=0;i<candidate_bit.size();i++)
    {
        cout<<candidate_bit[i].first<<" "<<candidate_bit[i].second<<endl;
    }

    //cb and ld
    bool flag=0;
    for (auto it=candidate_bit.begin();it!=candidate_bit.end();it++)
    {
        for (int j=0;j<e_left_diag_pos.size();j++)
        {
            if ((it->first == e_left_diag_pos[j].first) && (it->second == e_left_diag_pos[j].second))
            {
                flag=1;

                break;
            }
        }
        if (!flag)
        {
            candidate_bit.erase(it--);
        }
        flag=0;
    }
    cout<<"candidate bits:"<<endl;
    for (int i=0;i<candidate_bit.size();i++)
    {
        cout<<candidate_bit[i].first<<" "<<candidate_bit[i].second<<endl;
    }


    //cb and rd
    flag=0;
    for (auto it=candidate_bit.begin();it!=candidate_bit.end();it++)
    {
        for (int j=0;j<e_right_diag_pos.size();j++)
        {
            if ((it->first == e_right_diag_pos[j].first) && (it->second ==  e_right_diag_pos[j].second))
            {
                flag=1;
                break;
            }
        }
        if (!flag)
        {
            candidate_bit.erase(it--);
        }
        flag=0;
    }

    cout<<"candidate bits:"<<endl;
    for (int i=0;i<candidate_bit.size();i++)
    {
        cout<<candidate_bit[i].first<<" "<<candidate_bit[i].second<<endl;
    }

    return 0;
}

