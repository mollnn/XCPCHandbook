typedef pair<int,void*> abcd;
struct small_root_heap {
	abcd heap[M];
	int top;
	void push_up(int t) {
		while(t>1&&heap[t]<heap[t>>1])
					swap(heap[t],heap[t>>1]),swap( ((abcd*)heap[t].second)->second , ((abcd*)heap[t>>1].second)->second ),t>>=1;
	}
	void push_down(int t) {
		t<<=1;
		while(t<=top) {
			if(heap[t]>heap[t+1]&&t<top)
							t++;
			if(heap[t]<heap[t>>1])
							swap(heap[t],heap[t>>1]),swap( ((abcd*)heap[t].second)->second , ((abcd*)heap[t>>1].second)->second ),t<<=1; else break;
		}
	}
	void insert(int x) {
		heap[++top].first=x;
		push_up(top);
	}
	void pop() {
		heap[1]=heap[top--];
		((abcd*)heap[1].second)->second=&heap[1];
		push_down(1);
	}
	void del(abcd *x) {
		int t=x-heap;
		heap[t]=heap[top--];
		((abcd*)heap[t].second)->second=&heap[t];
		push_down(t);
		push_up(t);
	}
}
;
