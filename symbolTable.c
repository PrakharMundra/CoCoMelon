#define tableSize 1997
// this function is used to find the hash value of the string
long long hashFunc(char* inp)
{
    //we use the rolling polynomial hash method with formula s[i]*p^i mod m
    int prime=53; //prime number close to number of alphabets(upper and lowercase)
    long long power=1;
    int modulo=1e5+3;//large prime number (probability of collision is 1/modulo)
    long long res=0;//final key value to be returned
    for(int i=0;i<strlen(inp);i++)
    {
        res=(((inp[i]-'a'+1)*power)+res)%modulo;
        power=(power*prime)%modulo;
    }
    return res;
}
