ll exgcd(ll a, ll &ar, ll b)  //維護a*ar+b*as=gcd(a, b)
{
   ll as = 0, br = 0, bs = 1;
   while(a && b) 
   {
      ar -= br*(a/b);
      as -= bs*(a/b);
      a %= b;
      if(a == 0) break;
      br -= ar*(b/a);
      bs -= as*(b/a);
      b %= a;
   }
   if(a == 0) a = b, ar = br;  //維護a*ar+b*as=gcd(a, b)
   return a; //return gcd(a, b)
}

