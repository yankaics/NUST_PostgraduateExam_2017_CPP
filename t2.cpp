#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Graph{
	public:
		static const long MAX_PATH=1000000000;
		static const int MAX_SIZE=100;
		long arv[MAX_SIZE][MAX_SIZE];
		int n_point;
		long D[MAX_SIZE];
		int Short_Path[MAX_SIZE];
		bool S[MAX_SIZE];
		int Traver_Path[MAX_SIZE];
		bool Visited[MAX_SIZE]; 
		
		//���� 
		Graph(long a[MAX_SIZE][MAX_SIZE],int n){
			n_point=n;
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					arv[i][j]=a[i][j];
				}
			}
		}
		
		//�Ͻ�˹�����㷨 
		void ShortPath(){
			for(int i=0;i<n_point;i++){
				S[i]=false;
				D[i]=arv[0][i];
				if(arv[0][i]<MAX_PATH) Short_Path[i]=0;
				else Short_Path[i]=-1;
			}
			S[0]=true;
			Short_Path[0]=-1;
			D[0]=0;
			for(int i=1;i<n_point;i++){
				long min=MAX_PATH;
				int v=-1;
				for(int j=1;j<n_point;j++){
					if(!S[j]&&D[j]<min){
						min=D[j];
						v=j;
					}
				}
				S[v]=true;
				for(int j=1;j<n_point;j++){
					if(!S[j]&&D[v]+arv[v][j]<D[j]){
						D[j]=D[v]+arv[v][j];
						Short_Path[j]=v;
					}
				}
			}
		}
		
		//������ȱ���,���е���DT�㷨 
		void DeptTraver(int begin){
			for(int i=0;i<n_point;i++) Traver_Path[i]=-1;
			for(int i=0;i<n_point;i++) Visited[i]=false;
			DT(begin);
		}
		void DT(int begin){
			Visited[begin]=true;
			addTraverPath(begin);
			for(int v=FirstAdj(begin);v!=-1;v=NextAdj(begin,v)){
				if(!Visited[v]) DT(v);
			}
		} 
		
		//������ȱ���
		void BroadTraver(int begin){
			for(int i=0;i<n_point;i++) Traver_Path[i]=-1;
			for(int i=0;i<n_point;i++) Visited[i]=false;
			int queue[MAX_SIZE],front=0,rear=0;
			queue[rear]=begin; rear=(rear+1)%MAX_SIZE;
			while(front!=rear){
				int v=queue[front]; front=(front+1)%MAX_SIZE;
				addTraverPath(v);
				Visited[v]=true;
				for(int w=FirstAdj(v);w!=-1;w=NextAdj(v,w)){
					if(!Visited[w]){
						queue[rear]=w; rear=(rear+1)%MAX_SIZE;
					}
				}
			}
		} 
		
		//��һ���ڽӵ㣬�����ڽӵ㣬�򷵻�-1 
		int FirstAdj(int org){
			for(int i=0;i<n_point;i++){
				if(arv[org][i]<MAX_PATH) return i;
			}
			return -1;
		}
		
		//��һ���ڽӵ㣬������һ���ڽӵ㣬�򷵻�-1
		int NextAdj(int org,int now){
			for(int i=now+1;i<n_point;i++){
				if(arv[org][i]<MAX_PATH) return i;
			}
			return -1;
		}
		
		//�������·������ӽڵ� 
		void addTraverPath(int v){
			int i=0;
			while(Traver_Path[i]!=-1) i++;
			Traver_Path[i]=v;
		}
		
		//��ӡ����·��
		void outputTraverPath(){
			int i=0;
			while(Traver_Path[i]!=-1&&i<n_point){
				cout<<Traver_Path[i];
				if(!(i==n_point-1||Traver_Path[i+1]==-1)) cout<<"->";
				i++;
			}
			cout<<endl;
		} 
		 
		//��ӡ���·�� 
		void outputShortPath(int end){
			int i=end;
			int stack[MAX_SIZE],top=-1;
			stack[++top]=end;
			while(Short_Path[i]!=-1){
				stack[++top]=Short_Path[i];
				i=Short_Path[i];
			}
			while(top!=-1){
				cout<<stack[top--];
				if(top>-1) cout<<"->";
			}
			cout<<"\tPathLength:"<<D[end];
			cout<<endl;
		}
		
		//��ӡͼ�ṹ 
		void output(){
			for(int i=0;i<n_point;i++){
				for(int j=0;j<n_point;j++){
					cout<<arv[i][j]<<"  ";
				}
				cout<<endl;
			}	
		}
};


int main(){
	long arv[Graph::MAX_SIZE][Graph::MAX_SIZE];
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			arv[i][j]=Graph::MAX_PATH;
		}
	}
	for(int i=0;i<m;i++){
		int be,en;
		long pa;
		cin>>be>>en;
		cin>>pa;
		be--;
		en--;
		arv[be][en]=pa;
	}
	Graph graph(arv,n);
	graph.ShortPath();
	graph.outputShortPath(1);
	graph.outputShortPath(2);
	graph.outputShortPath(3);
	graph.outputShortPath(4);
	graph.BroadTraver(0);
	graph.outputTraverPath();
	return 0;
}


