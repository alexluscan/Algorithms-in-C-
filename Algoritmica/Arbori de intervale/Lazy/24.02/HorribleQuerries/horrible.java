
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Arrays;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class horrible{
    private static long tree[], helper[];
    private static boolean color[];

    public static void main (String [] args) throws IOException{
        BufferedReader br = new BufferedReader (new InputStreamReader (System.in));
        StringTokenizer st =null;
        int t = Integer.parseInt(br.readLine());
        for(;t>0;t--){
            st = new StringTokenizer (br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int C = Integer.parseInt(st.nextToken());
            init(N);
            for (int I=1;I<=C;I++){
                st = new StringTokenizer(br.readLine());
                if (st.nextToken().equals("0")){
                    int P = Integer.parseInt(st.nextToken());
                    int Q = Integer.parseInt(st.nextToken());
                    long V = Long.parseLong(st.nextToken());
                    update (1,1, N, P,Q, V);
                }
                else {
                    int P = Integer.parseInt(st.nextToken());
                    int Q = Integer.parseInt(st.nextToken());
                    long ans = sum_of_range (1,1,N, P,Q);
                    System.out.println(ans);
                }
            }
        }
    }

    private static void init(int N){
        tree = new long [262145];
        helper = new long [262145];
        color  = new boolean [262145];
        Arrays.fill (tree,0);
        Arrays.fill (helper, 0);
        Arrays.fill (color, false);
    }

    private static   void update (int node, int start, int end, int left, int right, long value){
        if (left > end || right <start )
            return ;
        if (start == end ){
            tree[node]+= value;
            if (color[node]==true){
                tree[node] += helper[node];
                helper[node]=0;
            }
            return;
        }
        if (left <=start && right >= end){
            helper[2*node] += value;
            helper[2*node+1] += value;
            color[2*node] = color[2*node+1] = true;
            tree[node] += (value *(end-start+1));
            return ;
        }
        else if (left <= end && right >end)
            tree[node ] += (value*(end-left+1));
        else if (start <= right && left <start)
            tree[node] += (value*(right-start+1));
        else if (left >= start && right <= end)
            tree[node] += (value*(right-left+1));

        update (2*node, start, (start+end)/2, left, right, value);
        update ((2*node)+1, ((start+end)/2)+1, end, left, right, value);
        return;
    }


    private static long sum_of_range (int node, int start, int end, int left, int right){
        if (left > end || right <start)
            return 0;
        if (color[node] == true){
            tree[node] += (helper[node] *(end-start+1));
            color[node]=false;
            if (start != end){
                color[2*node]=color[2*node+1] = true;
                helper[2*node] += helper[node];
                helper[2*node+1] += helper[node];
            }
            helper[node]=0;
        }
        if (left <= start && right >= end){
            return tree[node];
        }
        long s1 = sum_of_range(2*node, start, (start+end)/2, left, right);
        long s2 = sum_of_range(2*node+1,((start+end)/2)+1,end, left,right);
        return s1+s2;
    }
}

