struct List {
    int val;
    List* next;
    List(int n) : val(n), next(0) {}
    ~List() { delete next;}
};

int main() {
    List* lst = new List(9);
    lst->next = new List(9*2);
    lst->next->next = new List(9*3);
    delete lst->next->next;
    delete lst;
}
