#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

struct Movie {
    int id;
    string title;
    string genre;
    int year;
    int duration;

    Movie() : id(0), year(0), duration(0) {}
};

struct Node {
    Movie data;
    Node *prev;
    Node *next;

    Node(const Movie &m) : data(m), prev(NULL), next(NULL) {}
};

class DoublyList {
    Node *head;
    Node *tail;
    size_t sz;
    int next_id;

public:
    DoublyList() : head(NULL), tail(NULL), sz(0), next_id(1) {}

    ~DoublyList() { clear(); }

    int search_by_id_print(const string &q) {
        int id = safe_stoi(q);
        Node *cur = find_by_id(id);
        if (cur) {
            cout << "\n--- Pelicula encontrada ---\n";
            print_movie(cur->data);
            return 1;
        } else {
            cout << "No se encontro ninguna pelicula con ID '" << q << "'.\n";
            return 0;
        }
    }

    void clear() {
        while (head) {
            Node *tmp = head;
            head = head->next;
            delete tmp;
        }
        head = tail = NULL;
        sz = 0;
    }

    size_t size() const { return sz; }

    void push_back(const Movie &m) {
        Movie mc = m;
        handle_id(mc);
        Node *n = new Node(mc);
        if (!head) head = tail = n;
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        ++sz;
    }

    void push_front(const Movie &m) {
        Movie mc = m;
        handle_id(mc);
        Node *n = new Node(mc);
        if (!head) head = tail = n;
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        ++sz;
    }

    void insert_after(const Movie &m, int pos) {
        if (pos <= -1 || !head) { push_front(m); return; }
        if (pos >= (int)sz - 1) { push_back(m); return; }

        Node *cur = head;
        int i = 0;
        while (cur && i < pos) { cur = cur->next; ++i; }
        if (!cur) { push_back(m); return; }
        Movie mc = m;
        handle_id(mc);
        Node *n = new Node(mc);
        n->next = cur->next;
        n->prev = cur;
        if (cur->next) cur->next->prev = n;
        cur->next = n;
        if (cur == tail) tail = n;
        ++sz;
    }

private:
    void handle_id(Movie &m) {
        if (m.id <= 0) {
            m.id = next_id++;
        } else {
            if (m.id >= next_id) {
                next_id = m.id + 1;
            }
        }
    }
public:
    Node* find_first_by_title(const string &q) {
        string ql = tolower_copy(q);
        Node *cur = head;
        while (cur) {
            if (contains_ci(cur->data.title, ql)) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    Node* find_by_id(int id) {
        Node *cur = head;
        while (cur) {
            if (cur->data.id == id) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    int search_by_title_print(const string &q) {
        string ql = tolower_copy(q);
        Node *cur = head;
        int found = 0;
        while (cur) {
            if (contains_ci(cur->data.title, ql)) {
                cout << "\n--- Coincidencia #" << (found+1) << " ---\n";
                print_movie(cur->data);
                ++found;
            }
            cur = cur->next;
        }
        if (!found) cout << "No se encontro ninguna pelicula con '" << q << "' en el titulo.\n";
        return found;
    }

    void delete_node(Node *n) {
        if (!n) return;
        if (n->prev) n->prev->next = n->next;
        else head = n->next;
        if (n->next) n->next->prev = n->prev;
        else tail = n->prev;
        delete n;
        --sz;
    }

    void print_all_brief() const {
        Node *cur = head;
        while (cur) {
            cout << "ID: " << cur->data.id << "\n";
            print_movie(cur->data);
            cur = cur->next;
        }
    }

    bool save_to_csv(const string &filename) const {
        ofstream ofs(filename.c_str());
        if (!ofs) {
            cerr << "No se pudo abrir '" << filename << "' para escritura.\n";
            return false;
        }
        ofs << "id,title,genre,year,duration\n";
        Node *cur = head;
        while (cur) {
            ofs << cur->data.id << ",";
            write_field_csv(ofs, cur->data.title); ofs << ",";
            write_field_csv(ofs, cur->data.genre); ofs << ",";
            ofs << cur->data.year << "," << cur->data.duration << "\n";
            cur = cur->next;
        }
        return true;
    }

    int load_from_csv(const string &filename) {
    ifstream ifs(filename.c_str());
    if (!ifs) {
        cerr << "No se pudo abrir '" << filename << "' para lectura.\n";
        return 0;
    }
    
    clear(); 
    next_id = 1;

    string line;
    if (!getline(ifs, line)) return 0;
    vector<string> headers = parse_csv_line_simple(line);
    int idx_id=-1, idx_title=-1, idx_genre=-1, idx_year=-1, idx_duration=-1;

    for (size_t i=0; i < headers.size(); ++i) {
        string h = headers[i];
        tolower_inplace(h);
        if (h == "id") idx_id=i;
        else if (h == "title") idx_title=i;
        else if (h == "genres") idx_genre=i;
        else if (h == "release_date") idx_year=i;
        else if (h == "runtime") idx_duration=i;
    }

    int loaded = 0;
    while (getline(ifs, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) continue;
        vector<string> cols = parse_csv_line_simple(line);
        Movie m;

        if (idx_id != -1 && idx_id < (int)cols.size()) m.id = safe_stoi(cols[idx_id]);
        if (idx_title != -1 && idx_title < (int)cols.size()) m.title = trim_copy(cols[idx_title]);
        if (idx_genre != -1 && idx_genre < (int)cols.size()) m.genre = trim_copy(cols[idx_genre]);
        if (idx_duration != -1 && idx_duration < (int)cols.size()) m.duration = safe_stoi(cols[idx_duration]);
        
        if (idx_year != -1 && idx_year < (int)cols.size()) {
            string date_str = trim_copy(cols[idx_year]);
            if (date_str.length() >= 4) {
                 m.year = safe_stoi(date_str.substr(date_str.length() - 2));
                 if (m.year >= 0 && m.year <= 30) { m.year += 2000; }
                 else { m.year += 1900; }
            }
        }
        
        if (m.id <= 0 || m.title.empty()) continue;

        Node *n = new Node(m);
        if (!head) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        sz++;
        loaded++;
        
        if (m.id >= next_id) {
            next_id = m.id + 1;
        }
    }
    cout << "Se cargaron " << loaded << " peliculas desde '" << filename << "'.\n";
    return loaded;
}

    static string trim_copy(const string &s) {
        size_t a = 0, b = s.size();
        while (a < b && isspace((unsigned char)s[a])) ++a;
        while (b > a && isspace((unsigned char)s[b-1])) --b;
        return s.substr(a, b-a);
    }

    static void tolower_inplace(string &s) {
        for (size_t i = 0; i < s.size(); ++i) {
            s[i] = (char)tolower((unsigned char)s[i]);
        }
    }

    static string tolower_copy(const string &s) {
        string r = s;
        tolower_inplace(r);
        return r;
    }

    static bool contains_ci(const string &hay, const string &needle_lower) {
        string h = tolower_copy(hay);
        return h.find(needle_lower) != string::npos;
    }

    static int safe_stoi(const string &s) {
        string t = trim_copy(s);
        if (t.empty()) return 0;
        std::istringstream iss(t);
        int v = 0;
        if (iss >> v) return v;
        return 0;
    }

    static void print_movie(const Movie &m) {
        cout << "Titulo   : " << m.title << "\n";
        cout << "Genero   : " << m.genre << "\n";
        if (m.year > 0) cout << "Year     : " << m.year << "\n";
        if (m.duration > 0) cout << "Duracion : " << m.duration << " min \n";
    }

private:
    static vector<string> parse_csv_line_simple(const string &line) {
        vector<string> out;
        string cur;
        bool inquote = false;
        for (size_t i=0;i<line.size();++i) {
            char c = line[i];
            if (c == '"' ) {
                if (inquote && i+1 < line.size() && line[i+1] == '"') {
                    cur.push_back('"');
                    ++i;
                } else {
                    inquote = !inquote;
                }
            } else if (c == ',' && !inquote) {
                out.push_back(cur);
                cur.clear();
            } else {
                cur.push_back(c);
            }
        }
        out.push_back(cur);
        return out;
    }

    static void write_field_csv(ostream &os, const string &s) {
        bool need = false;
        for (size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (c == ',' || c == '"' || c == '\n' || c == '\r') {
                need = true;
                break;
            }
        }
        if (!need) {
            os << s;
            return;
        }
        os << '"';
        for (size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (c == '"')
                os << "\"";
            else
                os << c;
        }
        os << '"';
    }
};


static string input_line_trimmed(const string &prompt="") {
    if (!prompt.empty()) {
        cout << prompt;
        cout.flush();
    }
    string s;
    if (!getline(cin, s)) return string();
    size_t a=0, b=s.size();
    while (a<b && isspace((unsigned char)s[a])) ++a;
    while (b>a && isspace((unsigned char)s[b-1])) --b;
    return s.substr(a, b-a);
}

static void prompt_movie_input(Movie &m) {
    m.id = 0;
    m.title = input_line_trimmed("Titulo: ");
    m.genre = input_line_trimmed("Genero: ");
    string tmp;
    tmp = input_line_trimmed("Año (ej. 2010, 0 si desconocido): ");
    m.year = DoublyList::safe_stoi(tmp);
    tmp = input_line_trimmed("Duracion en minutos (0 si desconocido): ");
    m.duration = DoublyList::safe_stoi(tmp);
}
static void update_movie_interactive(Movie &m) {
    cout << "\nCampos disponibles para actualizar:\n"
        << "1) Titulo\n2) Género\n3) Año\n4) Duracion\n0) Cancelar\n";
    string opt = input_line_trimmed("Elija el numero del campo a modificar: ");
    int o = -1;
    {
        std::istringstream iss(opt);
        if (!(iss >> o)) o = -1;
    }
    string tmp;
    switch (o) {
        case 1:
            tmp = input_line_trimmed("Nuevo titulo: "); if (!tmp.empty()) m.title = tmp; break;
        case 2:
            tmp = input_line_trimmed("Nuevo genero: "); if (!tmp.empty()) m.genre = tmp; break;
        case 3:
            tmp = input_line_trimmed("Nuevo año: "); m.year = DoublyList::safe_stoi(tmp); break;
        case 4:
            tmp = input_line_trimmed("Nueva duracion (min): "); m.duration = DoublyList::safe_stoi(tmp); break;
        default:
            cout << "Actualizacion cancelada o opcion invalida.\n";
            return;
    }
    cout << "Actualizacion realizada.\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    DoublyList lista;
    for (;;) {
        cout << "\n===     MENU     ===\n"
            << "1) Cargar desde CSV (Movies.csv)\n"
            << "2) Buscar pelicula por titulo\n"
            << "3) Buscar pelicula por ID\n"
            << "4) Insertar nueva pelicula\n"
            << "5) Eliminar pelicula por titulo\n"
            << "6) Actualizar datos de una pelicula\n"
            << "7) Guardar lista a CSV (salida.csv)\n"
            << "8) Mostrar todas las peliculas\n"
            << "0) Salir\n";

        string opt = input_line_trimmed("Elige una opcion: ");
        int o = -1;
        {
            std::istringstream iss(opt);
            if (!(iss >> o)) o = -1;
        }

        if (o == 1) {
            string fname = input_line_trimmed("Nombre del archivo CSV (por defecto 'Movies.csv'): ");
            if (fname.empty()) fname = "Movies.csv";
            lista.load_from_csv(fname);
        }
        else if (o == 2) {
            string q = input_line_trimmed("Ingrese titulo o parte del titulo a buscar: ");
            if (q.empty()) { cout << "Busqueda vacia.\n"; continue; }
            lista.search_by_title_print(q);
        }
        else if (o == 3) {
            string q = input_line_trimmed("Ingrese ID de la pelicula a buscar: ");
            if (q.empty()) { cout << "Busqueda vacia.\n"; continue; }
            lista.search_by_id_print(q);
        }
        else if (o == 4) {
            string subopt = input_line_trimmed("Insertar en: 1) Inicio 2) Final 3) Despues de posicion (0..n-1)  Opc: ");
            int sub = 2;
            {
                std::istringstream iss(subopt);
                if (!(iss >> sub)) sub = 2;
            }
            Movie m;
            prompt_movie_input(m);
            if (m.title.empty()) {
                cout << "El titulo no puede estar vacio. Operacion cancelada.\n";
                continue;
            }
            if (sub == 1) lista.push_front(m);
            else if (sub == 2) lista.push_back(m);
            else if (sub == 3) {
                string posS = input_line_trimmed("Ingrese posicion (0..n-1). Si pos >= tamaño, se inserta al final: ");
                int pos = 0;
                {
                    std::istringstream iss(posS);
                    if (!(iss >> pos)) pos = (int)lista.size()-1;
                }
                lista.insert_after(m, pos);
            } else lista.push_back(m);
            cout << "Pelicula insertada.\n";
        }
        else if (o == 5) {
            string q = input_line_trimmed("Ingrese titulo (o parte) de la pelicula a eliminar: ");
            if (q.empty()) { cout << "Busqueda vacia.\n"; continue; }
            Node *found = lista.find_first_by_title(q);
            if (!found) {
                cout << "No se encontro ninguna pelicula con '" << q << "'.\n";
            } else {
                cout << "Se encontro la siguiente pelicula:\n";
                DoublyList::print_movie(found->data);
                string r = input_line_trimmed("Desea eliminarla? (s/n): ");
                if (!r.empty() && (r[0]=='s' || r[0]=='S')) {
                    lista.delete_node(found);
                    cout << "Pelicula eliminada.\n";
                } else cout << "Eliminacion cancelada.\n";
            }
        }
        else if (o == 6) {
            string q = input_line_trimmed("Ingrese ID de la pelicula a actualizar: ");
            if (q.empty()) { cout << "Busqueda vacia.\n"; continue; }
            int id_to_update = DoublyList::safe_stoi(q);
            Node *found = lista.find_by_id(id_to_update);
            
            if (!found) {
                cout << "No se encontro ninguna pelicula con ID '" << q << "'.\n";
            } else {
                cout << "Pelicula encontrada:\n";
                DoublyList::print_movie(found->data);
                update_movie_interactive(found->data);
            }
        }
        else if (o == 7) {
            string fname = input_line_trimmed("Archivo destino (por defecto 'salida.csv'): ");
            if (fname.empty()) fname = "salida.csv";
            if (lista.save_to_csv(fname)) cout << "Lista guardada en '" << fname << "'.\n";
            else cout << "Error al guardar en '" << fname << "'.\n";
        }
        else if (o == 8) {
            lista.print_all_brief();
        }
        else if (o == 0) {
            string s = input_line_trimmed("Saliendo. Guardar antes de salir? (s/n): ");
            if (!s.empty() && (s[0]=='s' || s[0]=='S')) {
                if (lista.save_to_csv("salida.csv")) cout << "Guardado en 'salida.csv'.\n";
                else cout << "No se pudo guardar en 'salida.csv'.\n";
            }
            break;
        }
        else {
            cout << "Opcion no valida.\n";
        }
    }

    return 0;
}