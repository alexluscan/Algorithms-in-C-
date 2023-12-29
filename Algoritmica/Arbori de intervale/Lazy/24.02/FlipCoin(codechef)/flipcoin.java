public static void main(String[] args) throws IOException
{
  int n = in.readInt();  // Using Fast I/O in Java
  int q = in.readInt();
  flip = new int[8*n+1];
  heads = new int[8*n+1];
  construct_tree(1,0,n-1);
  for(i=0;i<q;i++)
  {
      str = br.readLine();
      int spIndex = str.indexOf(" ");
      int query = in.readInt();
      int start = in.readInt();
      int end = in.readInt();
      if(query ==0)
      {
               update_tree(1,0,n-1,start,end);
      }
      else
      {
               head_count=0;
               get_result(1,0,n-1,start,end);
               System.out.println(head_count);
      }
    }
 }
public static void get_result(int present,int start,int end, int i, int j)
{
   if(start>j || end <i)
   {
      if(flip[present]%2==0)
      {
          flip[present]=0;
      }
      else
      {
          heads[present]= end - start +1 - heads[present];
          flip[2*present] += flip[present];
          flip[2*present+1] += flip[present];
          flip[present]=0;
      }
      return;
    }
    if(start>=i && end<=j)
    {
        if(flip[present]%2!=0)
        {
            head_count = head_count + end - start +1 - heads[present];
            flip[2*present] += flip[present];
            flip[2*present+1] += flip[present];
            flip[present]=0;
            heads[present] = end - start +1 - heads[present];
         }
         else
         {
              head_count = head_count + heads[present];
              flip[present]=0;
         }
         return;
     }
     int mid = (start+end)/2;
     flip[2*present] += flip[present];
     flip[2*present+1]+=flip[present];
     flip[present]=0;
     get_result(2*present,start,mid,i,j);
     get_result(2*present+1,mid+1,end,i,j);
     heads[present] = heads[2*present]+heads[2*present+1];
 }
public static void update_tree(int present,int begin,int end,int i,int j)
 {
      if(begin > j || end < i)
      {
           if(flip[present]%2==0)
           {
              flip[present]=0;
           }
           else
           {
              heads[present]= end - begin +1 - heads[present];
              flip[2*present] += flip[present];
              flip[2*present+1] += flip[present];
              flip[present]=0;
           }
           return;
        }
        if(begin >=i && end <=j)
        {
           flip[present] = flip[present]+1;
           if(flip[present]%2!=0)
           {
               heads[present]= end - begin +1 -heads[present];
               flip[2*present] += flip[present];
               flip[2*present+1] += flip[present];
               flip[present]=0;
           }
           else
           {
               flip[present]=0;
           }
           return;
       }
       int mid = (begin + end)/2;
       flip[2*present]+= flip[present];
       flip[2*present+1] += flip[present];
       flip[present]=0;
       update_tree(2*present,begin,mid,i,j);
       update_tree(2*present+1,mid+1,end,i,j);
       heads[present] = heads[2*present]+heads[2*present+1];
       return;
 }
 public static void construct_tree(int present,int start, int last)
 {
     int mid;
     if(start==last)
     {
         flip[present]=0;
         heads[present]=0;
         return ;
     }
     mid = (start + last)/2;
     construct_tree(2*present,start,mid);
     construct_tree(2*present+1,mid+1,last);
     flip[present] = flip[2*present]+flip[2*present+1];
     heads[present] = heads[2*present]+heads[2*present+1];
     return;
 }
