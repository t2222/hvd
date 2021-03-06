#include <bits/stdc++.h>
// final hvd
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

    int m, n;
    cin >> m >> n;
    bool input[m][n];
    bool errored_matrix[m][n];
    bool r_xor, c_xor;
    bool row_parity[m];
    bool col_parity[n];

    srand((unsigned) time(0));
    cout<<"Input:"<<endl;

    for (int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            input[i][j] = rand() % 2;
            errored_matrix[i][j] = input[i][j];
            cout<<input[i][j]<<" ";
            if (j == 0)
            {
                r_xor = input[i][j];
            }
            else
                r_xor ^= input[i][j];
            if (i == 0)
            {
                col_parity[j] = input[i][j];
            }
            else
                col_parity[j] ^= input[i][j];
        }
        cout<<endl;
        row_parity[i] = r_xor;
    }

    cout << endl;

    cout << "row parity: \n";
    print_1d_parity(row_parity,m);
    cout << "col parity: \n";
    print_1d_parity(col_parity,n);

    // diagonal parity
    //left
    bool left_diag_parity[m+n], right_diag_parity[m+n];
    left_diag_parity[0] = input[0][0];
    right_diag_parity[0] = input[0][n-1];

    for (int i=1; i<m; i++)
    {
        int row=i;
        int col=0;
        left_diag_parity[i]=input[row--][col++];
        while (col < n && row >= 0)
        {
            left_diag_parity[i] ^= input[row--][col++];
        }
    }
    for (int j = 1; j < n-1 ; j++)
    {
        int row=m-1;
        int col=j;
        left_diag_parity[m+j-1]=input[row--][col++];
        while (row>=0 && col<n)
        {
            left_diag_parity[m+j-1] ^= input[row--][col++];
        }
    }

    left_diag_parity[m+n-2]=input[m-1][n-1];
    cout<<endl<<"Left diagonal parity:"<<endl;
    for (int i=0; i<m+n-1; i++)
    {
        cout<<left_diag_parity[i]<<" ";
    }
    cout<<endl;
    // right
    for (int i=1; i<m; i++)
    {
        int row=i;
        int col=n-1;
        right_diag_parity[i]=input[row--][col--];
        while (col>=0 && row>=0)
        {
            right_diag_parity[i] ^= input[row--][col--];
        }
    }
    for (int j = n-2; j>=0 ; j--)
    {
        int row=m-1;
        int col=j;
        right_diag_parity[m+n-j-2]=input[row--][col--];
        while (row>=0 && col>=0)
        {
            right_diag_parity[m+n-j-2] ^= input[row--][col--];
        }
    }

    right_diag_parity[m+n-2]=input[m-1][0];

    cout<<endl<<"Right diagonal parity:"<<endl;
    for (int i=0; i<m+n-1; i++)
        cout<<right_diag_parity[i]<<" ";
    cout<<endl;

    // error postion generation
    unordered_set<int> position_set;
    const int no_of_errored_positions = 3;
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
        // cout << *itr << " ";
    }

//    for (int i = 0 ; i < 6 ; i++)
//    {
//        cout << positions[i] << " ";
//    }
    cout << endl;

    // error injection
    for (int i = 0 ; i < total_pos ; i+=2)
    {
        int p1 = positions[i], p2 = positions[i+1];
        cout << p1 << " " << p2 << endl;
        errored_matrix[p1][p2] = flip_bit(errored_matrix[p1][p2]);
    }

    bool e_r_xor, e_c_xor;
    bool e_row_parity[m];
    bool e_col_parity[n];

    // h,v parity
    cout << "errored matrix: \n";
    for (int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            if (j == 0)
            {
                e_r_xor = errored_matrix[i][j];
            }
            else
                e_r_xor ^= errored_matrix[i][j];
            if (i == 0)
            {
                e_col_parity[j] = errored_matrix[i][j];
            }
            else
                e_col_parity[j] ^= errored_matrix[i][j];

            cout << errored_matrix[i][j] << " ";
        }
        cout << "\n";
        e_row_parity[i] = e_r_xor;
    }

    cout << "errored row parity: "<<endl;
    print_1d_parity(e_row_parity,m);
    cout << "errored col parity: "<<endl;
    print_1d_parity(e_col_parity,n);


    // d, d` parity
    // left
    bool e_left_diag_parity[m+n], e_right_diag_parity[m+n];
    e_left_diag_parity[0] = errored_matrix[0][0];
    e_right_diag_parity[0] = errored_matrix[0][n-1];

    for (int i=1; i<m; i++)
    {
        int row=i;
        int col=0;
        e_left_diag_parity[i]=errored_matrix[row--][col++];
        while (col < n && row >= 0)
        {
            e_left_diag_parity[i] ^= errored_matrix[row--][col++];
        }
    }
    for (int j = 1; j < n-1 ; j++)
    {
        int row=m-1;
        int col=j;
        e_left_diag_parity[m+j-1]=errored_matrix[row--][col++];
        while (row>=0 && col<n)
        {
            e_left_diag_parity[m+j-1] ^= errored_matrix[row--][col++];
        }
    }

    e_left_diag_parity[m+n-2]=errored_matrix[m-1][n-1];

    cout<<endl<<"Left diagonal parity:"<<endl;
    for (int i=0; i<m+n-1; i++)
    {
        cout<<e_left_diag_parity[i]<<" ";
    }
    cout<<endl;
    // right
    for (int i=1; i<m; i++)
    {
        int row=i;
        int col=n-1;
        e_right_diag_parity[i]=errored_matrix[row--][col--];
        while (col>=0 && row>=0)
        {
            e_right_diag_parity[i] ^= errored_matrix[row--][col--];
        }
    }
    for (int j = n-2; j>=0 ; j--)
    {
        int row=m-1;
        int col=j;
        e_right_diag_parity[m+n-j-2]=errored_matrix[row--][col--];
        while (row>=0 && col>=0)
        {
            e_right_diag_parity[m+n-j-2] ^= errored_matrix[row--][col--];
        }
    }

    e_right_diag_parity[m+n-2]=errored_matrix[m-1][0];

    cout<<endl<<"Right diagonal parity:"<<endl;
    for (int i=0; i<m+n-1; i++)
        cout<<e_right_diag_parity[i]<<" ";
    cout<<endl;

    //candidate positions
    vector<int> c_row_parity_pos;
    vector<int> c_col_parity_pos;
    vector<int> c_left_diag_parity_pos;
    vector<int> c_right_diag_parity_pos;

    for (int i=0; i<m+n-1; i++)
    {
        if (i<m)
        {
            if (row_parity[i]!=e_row_parity[i])
            {
                c_row_parity_pos.push_back(i);
            }
        }
        if (i<n)
        {
            if (col_parity[i]!=e_col_parity[i])
            {
                c_col_parity_pos.push_back(i);
            }
        }
        if (left_diag_parity[i]!=e_left_diag_parity[i])
        {
            c_left_diag_parity_pos.push_back(i);
        }
        if (right_diag_parity[i]!=e_right_diag_parity[i])
        {
            c_right_diag_parity_pos.push_back(i);
        }
    }
    vector<pair<int,int>> candidate_pos;

    //row & col
    for (auto it1=c_row_parity_pos.begin(); it1!=c_row_parity_pos.end(); it1++)
    {
        for (auto it2=c_col_parity_pos.begin(); it2!=c_col_parity_pos.end(); it2++)
        {
            candidate_pos.push_back(make_pair(*it1,*it2));
        }
    }
    //left diagonal
    vector<pair<int,int>> left_diag_col_pos;
    cout<<"changed left diagonal parity: ";
    for (int i=0; i<c_left_diag_parity_pos.size(); i++)
    {
        cout<<c_left_diag_parity_pos[i]<<" ";
        if (c_left_diag_parity_pos[i]==0)
        {
            left_diag_col_pos.push_back(make_pair(0,0));
        }
        else if (c_left_diag_parity_pos[i]== (m+n-2))
        {
            left_diag_col_pos.push_back(make_pair(m-1,n-1));
        }
        else if (c_left_diag_parity_pos[i]<m)
        {
            int row=c_left_diag_parity_pos[i];
            int col=0;
            left_diag_col_pos.push_back(make_pair(row--,col++));
            while (row>=0 && col<n)
            {
                left_diag_col_pos.push_back(make_pair(row--,col++));
            }
        }
        else
        {
            int row=m-1;
            int col=c_left_diag_parity_pos[i]-n+1;
            left_diag_col_pos.push_back(make_pair(row--,col++));
            while (row>=0 && col<n)
            {
                left_diag_col_pos.push_back(make_pair(row--,col++));
            }
        }
    }
    cout<<endl;
    //row & left diagonal
    for (int i=0; i<c_row_parity_pos.size(); i++)
    {
        for (int j=0; j<left_diag_col_pos.size(); j++)
        {
            if (c_row_parity_pos[i]==left_diag_col_pos[j].first)
            {
                candidate_pos.push_back(left_diag_col_pos[j]);
            }
        }
    }

    //col & left diagonal
    for (int i=0; i<c_col_parity_pos.size(); i++)
    {
        for (int j=0; j<left_diag_col_pos.size(); j++)
        {
            if (c_col_parity_pos[i]==left_diag_col_pos[j].second)
            {
                candidate_pos.push_back(left_diag_col_pos[j]);
            }
        }
    }

    //right diagonal
    vector<pair<int,int>> right_diag_pos;
    cout<<"changed right diagonal parity: ";
    for (int i=0; i<c_right_diag_parity_pos.size(); i++)
    {
        cout<<c_right_diag_parity_pos[i]<<" ";
        if (c_right_diag_parity_pos[i]==0)
        {
            right_diag_pos.push_back(make_pair(0,n-1));
        }
        else if (c_right_diag_parity_pos[i]== (m+n-2))
        {
            right_diag_pos.push_back(make_pair(m-1,0));
        }
        else if (c_right_diag_parity_pos[i]<m)
        {
            int row=c_right_diag_parity_pos[i];
            int col=n-1;
            right_diag_pos.push_back(make_pair(row--,col--));
            while (col>=0 && row>=0)
            {
                right_diag_pos.push_back(make_pair(row--,col--));
            }
        }
        else
        {
            int row=m-1;
            int col=2*n-c_right_diag_parity_pos[i]-2;
            right_diag_pos.push_back(make_pair(row--,col--));
            while (row>=0 && col>=0)
            {
                right_diag_pos.push_back(make_pair(row--,col--));
            }
        }
    }
    cout<<endl;

    //row & right diagonal
    for (int i=0; i<c_row_parity_pos.size(); i++)
    {
        for (int j=0; j<right_diag_pos.size(); j++)
        {
            if (c_row_parity_pos[i]==right_diag_pos[j].first)
            {
                candidate_pos.push_back(right_diag_pos[j]);
            }
        }
    }

    //col & right diagonal
    for (int i=0; i<c_col_parity_pos.size(); i++)
    {
        for (int j=0; j<right_diag_pos.size(); j++)
        {
            if (c_col_parity_pos[i]==right_diag_pos[j].second)
            {
                candidate_pos.push_back(right_diag_pos[j]);
            }
        }
    }

    //left & right diagonal
    for (int i=0; i<left_diag_col_pos.size(); i++)
    {
        for (int j=0; j<right_diag_pos.size(); j++)
        {
            if ((left_diag_col_pos[i].first==right_diag_pos[j].first) && (left_diag_col_pos[i].second==right_diag_pos[j].second))
            {
                candidate_pos.push_back(right_diag_pos[j]);
            }
        }
    }
    vector<pair<int,int>> sorted_candidate_pos;
    int candidate_mat[m][n];
    int cnt=1;
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            candidate_mat[i][j]=0;
            for (int k=0; k<candidate_pos.size(); k++)
            {
                if ((i==candidate_pos[k].first) && (j==candidate_pos[k].second))
                {
                    candidate_mat[i][j]=cnt++;
                    sorted_candidate_pos.push_back(make_pair(i,j));
                    break;
                }
            }
        }
    }
    cout<<"candidate matrix:"<<endl;
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout<<candidate_mat[i][j]<<" ";
        }
        cout<<endl;
    }
//    cout<<endl<<"Sorted candidate position: "<<endl;
//    for (int i=0; i<sorted_candidate_pos.size(); i++)
//    {
//        cout<<sorted_candidate_pos[i].first<<" "<<sorted_candidate_pos[i].second<<endl;
//    }
//    cout<<endl;
    cout<<"changed row positions: ";
    for (int j=0; j<c_row_parity_pos.size(); j++)
    {
        cout<<c_row_parity_pos[j]<<" ";
    }
    cout<<endl<<"changed col position: ";
    for (int j=0; j<c_col_parity_pos.size(); j++)
    {
        cout<<c_col_parity_pos[j]<<" ";
    }
    cout<<"changed left diagonal positon:"<<endl;
    for (int j=0; j<left_diag_col_pos.size(); j++)
    {
        cout<<left_diag_col_pos[j].first<<" "<<left_diag_col_pos[j].second<<endl;
    }
    cout<<"changed right diagonal positon:"<<endl;
    for (int j=0; j<right_diag_pos.size(); j++)
    {
        cout<<right_diag_pos[j].first<<" "<<right_diag_pos[j].second<<endl;
    }

    cout<<"Start of refinement"<<endl;
    int flag=-1;

    for (auto it=sorted_candidate_pos.begin(); it!=sorted_candidate_pos.end(); ++it)
    {
        bool rf=0;

        for (int j=0; j<c_row_parity_pos.size(); j++)
        {
            if (c_row_parity_pos.size()==3)
            {
                if (it->first==c_row_parity_pos[j])
                {
                    rf=0;
                    break;
                }
                else
                {
                    rf=1;
                }
            }
            else
                flag=0;

        }
        if (rf)
        {
            sorted_candidate_pos.erase(it--);
            continue;
        }
        bool cf=0;

        for (int j=0; j<c_col_parity_pos.size(); j++)
        {
            if (c_col_parity_pos.size()==3)
            {
                if (it->second==c_col_parity_pos[j])
                {
                    cf=0;
                    break;
                }
                else
                {
                    cf=1;
                }
            }
            else
                flag=1;

        }
        if (cf)
        {
            sorted_candidate_pos.erase(it--);
            continue;
        }
        bool ldf=0;

        for (int j=0; j<left_diag_col_pos.size(); j++)
        {
            if (c_left_diag_parity_pos.size()==3)
            {
                if ((it->first==left_diag_col_pos[j].first) && (it->second==left_diag_col_pos[j].second))
                {
                    ldf=0;
                    break;
                }
                else
                    ldf=1;
            }
            else
                flag=2;

        }
        if (ldf)
        {
            sorted_candidate_pos.erase(it--);
            continue;
        }
        bool rdf=0;

        for (int j=0; j<right_diag_pos.size(); j++)
        {
            if (c_right_diag_parity_pos.size()==3)
            {
                if ((it->first==right_diag_pos[j].first) && (it->second==right_diag_pos[j].second))
                {
                    rdf=0;
                    break;
                }
                else
                    rdf=1;
            }
            else
                flag=3;

        }
        if (rdf)
        {
            sorted_candidate_pos.erase(it--);
        }
    }
    if (flag==-1)
    {
        cout<<endl<<"Error position: "<<endl;
        for (int i=0; i<sorted_candidate_pos.size(); i++)
        {
            cout<<sorted_candidate_pos[i].first<<" "<<sorted_candidate_pos[i].second<<endl;
        }
        cout<<endl;
    }
    else
    {
//        cout<<endl<<"refined candidate position: "<<endl;
//        for (int i=0; i<sorted_candidate_pos.size(); i++)
//        {
//            cout<<sorted_candidate_pos[i].first<<" "<<sorted_candidate_pos[i].second<<endl;
//        }
//        cout<<endl;
        vector<pair<int,int>> error_pos;
        if (flag==0)
        {
            for (auto it=sorted_candidate_pos.begin(); it!=sorted_candidate_pos.end(); ++it)
            {
                bool rf=0;

                for (int j=0; j<c_row_parity_pos.size(); j++)
                {

                    if (it->first==c_row_parity_pos[j])
                    {
                        rf=0;
                        break;
                    }
                    else
                    {
                        rf=1;
                    }

                }
                if (!rf)
                {
                    error_pos.push_back(make_pair(it->first,it->second));
                }
            }

        }
        else if (flag==1)
        {
            for (auto it=sorted_candidate_pos.begin(); it!=sorted_candidate_pos.end(); ++it)
            {
                bool cf=0;

                for (int j=0; j<c_col_parity_pos.size(); j++)
                {

                    if (it->second==c_col_parity_pos[j])
                    {
                        cf=0;
                        break;
                    }
                    else
                    {
                        cf=1;
                    }

                }
                if (!cf)
                {
                    error_pos.push_back(make_pair(it->first,it->second));
                }
            }
        }
        else if (flag==2)
        {
            for (auto it=sorted_candidate_pos.begin(); it!=sorted_candidate_pos.end(); ++it)
            {
                bool ldf=0;

                for (int j=0; j<left_diag_col_pos.size(); j++)
                {

                    if ((it->first==left_diag_col_pos[j].first) && (it->second==left_diag_col_pos[j].second))
                    {
                        ldf=0;
                        break;
                    }
                    else
                    {
                        ldf=1;
                    }

                }
                if (!ldf)
                {
                    error_pos.push_back(make_pair(it->first,it->second));
                }
            }
        }
        else
        {
            for (auto it=sorted_candidate_pos.begin(); it!=sorted_candidate_pos.end(); ++it)
            {
                bool rdf=0;

                for (int j=0; j<right_diag_pos.size(); j++)
                {

                    if ((it->first==right_diag_pos[j].first) && (it->second==right_diag_pos[j].second))
                    {
                        rdf=0;
                        break;
                    }
                    else
                    {
                        rdf=1;
                    }

                }
                if (!rdf)
                {
                    error_pos.push_back(make_pair(it->first,it->second));
                }
            }
        }
        for (auto it=sorted_candidate_pos.begin(); it!=sorted_candidate_pos.end(); ++it)
        {

            for (int i=0;i<error_pos.size();i++)
            {
                if (it->first==error_pos[i].first)
                {
                    sorted_candidate_pos.erase(it--);
                }
                if (it->second==error_pos[i].second)
                {
                    sorted_candidate_pos.erase(it--);
                }
                int row=error_pos[i].first;
                int col=error_pos[i].second;
                while (row<m && col>=0)
                {
                    row++;
                    col--;
                    if ((it->first==row) && (it->second==col))
                    {
                        sorted_candidate_pos.erase(it--);
                        break;
                    }
                }
                row=error_pos[i].first;
                col=error_pos[i].second;
                while (row<m && col<n)
                {
                    row++;
                    col++;
                    if ((it->first==row) && (it->second==col))
                    {
                        sorted_candidate_pos.erase(it--);
                        break;
                    }

                }
            }
        }
        for (auto it=sorted_candidate_pos.begin(); it!=sorted_candidate_pos.end(); ++it)
        {
            error_pos.push_back(make_pair(it->first,it->second));
        }
        cout<<"error positions:"<<endl;
        for (int i=0;i<error_pos.size();i++)
        {
            cout<<error_pos[i].first<<" "<<error_pos[i].second<<endl;
        }

    }

    return 0;
}
