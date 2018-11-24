ll SZ,MOD;
const int MAXSZ=105;

struct Mat
{
    ll m[MAXSZ][MAXSZ];
    Mat(){memset(m, 0, sizeof(m));}
};

Mat matMul(const Mat &A, const Mat &B)
{
    Mat rtn;
    for(int i = 0; i < SZ; i++)
        for(int k = 0; k < SZ; k++)
            if(A.m[i][k])for(int j = 0; j < SZ; j++)
            {
                rtn.m[i][j]+=(A.m[i][k]*B.m[k][j]);
            }
    return rtn;
}
//B is of size SZ
vector<ll> matMul(const Mat &A, const vector<ll> &B)
{
    vector<ll> rtn(SZ,0);
    for(int i = 0; i < SZ; i++)
        for(int j = 0; j < SZ; j++)
            rtn[i]=(rtn[i]+A.m[i][j]*B[j]);

    return rtn;
}

Mat matPow(Mat& M, ll p)
{
    if(p == 0)
    {
        Mat iden;
        for(int i=0;i<SZ;i++)iden.m[i][i]=1;
        return iden;
    }
    if(p == 1)return M;
    Mat rtn = matPow(M, p/2);
    if(p&1)return matMul(matMul(rtn, rtn), M);
    else return matMul(rtn, rtn);
}
