namespace MyDSA
{
    template <typename T> 
    ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
    {
        ListNodePosi(T) node = new ListNode<T>(e,prev,this);
        prev->succ = node;
        prev = node;
        return node;
    }

    template <typename T>    
    ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
    {
        ListNodePosi(T) node = new ListNode<T>(e,this,succ);
        succ->prev = node;
        succ = node;
        return node;
    }
}