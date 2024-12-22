#include <iostream>
#include <list>


//You must provide the following operations in amortized O(1) time:
//openDocument(docID): Load a new document into memory; if at capacity, evict the LRU doc.
//editDocument(docID): Mark that doc as the most recently edited. If the doc is not open, do nothing (or optionally treat it as openDocument—the behavior is up to you).
//closeDocument(docID): Close an open document (if it’s open).
//isOpen(docID): Return whether the document is currently loaded/open.

class recently_edited_documents{
private:
    std::list<std::string> documents;
    using iterator = std::list<std::string>::iterator;
    std::unordered_map<std::string,iterator> hash_table;
    size_t capacity;
    
public:
    recently_edited_documents(size_t capacity) : capacity(capacity){}
    void open_document(const std::string& doc_id){
        auto it = hash_table.find(doc_id);
        if(it != hash_table.end())
            return;
        if(documents.size() == capacity){
            auto iter = documents.end();
            iter--;
            hash_table.erase(*iter);
            documents.pop_back();
        }
        documents.push_front(doc_id);
        hash_table[doc_id] = documents.begin();
    }
    
    void edit_document(const std::string& doc_id){
        auto it = hash_table.find(doc_id);
        if(it == hash_table.end())
            return;
        
        documents.splice(documents.begin(), documents,it->second);
        hash_table[doc_id] = documents.begin();
    }
    
    void close_document(const std::string& doc_id){
        auto it = hash_table.find(doc_id);
        if(it == hash_table.end())
            return;
        documents.erase(it->second);
        hash_table.erase(doc_id);
    }
    
    bool is_open(const std::string& doc_id) const{
        auto it = hash_table.find(doc_id);
        if(it != hash_table.end())
            return true;
        return false;
    }
    
    void print_docs() const{
        for(auto it = documents.begin();it!=documents.end();it++)
            std::cout<<*it<<std::endl;
    }
};

int main(int argc, const char * argv[]) {
    recently_edited_documents docs(3);
    docs.open_document("file.exp");
    docs.open_document("sets.dat");
    docs.open_document("multi_set.dat");
    docs.open_document("evens.txt");
    docs.edit_document("evens.txt");
    std::cout<<docs.is_open("file.exp")<<std::endl;
    std::cout<<docs.is_open("sets.dat")<<std::endl;
    docs.close_document("sets.dat");
    docs.edit_document("evens.txt");
    
    docs.print_docs();
}
