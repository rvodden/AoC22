#include <bitset>
#include <deque>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

namespace aoc {

int64_t part_a(const std::string &inventory);
uint64_t part_b(const std::string &inventory);

using Rock = std::vector<std::vector<bool>>;

void parse_inventory(std::vector<char> &directions, const std::string &inventory);

std::ostream& operator<< (std::ostream &stream, const std::vector<std::bitset<7>>&) {
  return stream;
}

template < template<class, class> class C, class I, class A = std::allocator<I>>
class Cycler {
  public:
    Cycler(C<I, A> s) : _collection(s), _current( _collection.begin() ) {};
    
    Cycler(Cycler<C, I> &c) : _collection(c._collection), _current( _collection.begin() ) {};
    Cycler& operator=(const Cycler<C, I> &c) {
      _collection = c._collection;
      _current = _collection.begin();
      return *this;
    }
    
    ~Cycler() = default;


    I next() {
        if (_current == _collection.end() ) {
          _current = _collection.begin();
        }
        I t = *_current;
        _current++;
        _idx++;
        return t;
    };
    std::size_t state() const { return std::ranges::distance(_current, _collection.end()); };
    void reset() { _current = _collection.begin(); _idx = 0; };

  private:
    C<I, A>           _collection;
    C<I, A>::iterator _current;
    unsigned int      _idx = 0;
};

class Chamber {
  public:
    explicit Chamber(Cycler<std::vector, char> dp) : _direction_provider(dp) {};

    void add_rock(const std::vector<std::bitset<7>>&);
    void print   () const;
    void print   (const std::vector<std::bitset<7>>&, const std::deque<std::bitset<7>>::iterator&) const;

    std::size_t                 size                    () const { return _chamber.size(); };
    void                        clean                   ();
    void                        clear                   () { _chamber.clear(); };

    void                        log                     (const std::string &s) const { if(_print_enabled) std::cout << s << std::endl; };
    void                        add_row                 () { _chamber.push_front(0b0000000); _chamber_height++; };
    void                        ensure_n_clear_rows     (std::size_t n);
    void                        process_direction       (std::vector<std::bitset<7>> &new_rows,
                                                         const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window);

    void                        left                    (std::vector<std::bitset<7>> &new_rows,
                                                         const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window);
    void                        right                   (std::vector<std::bitset<7>> &new_rows,
                                                         const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window);
    void                        down                    (std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window) const;

    bool                        clash                   (const std::vector<std::bitset<7>> &rock_rows,
                                                         const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window) const;

    bool                        descent_would_block     (const std::vector<std::bitset<7>> &rock_rows,
                                                         std::vector<std::deque<std::bitset<7>>::iterator> sliding_window) const;

    uint64_t                    hash                    () const;

    std::vector<std::bitset<7>> rock_to_rows            (const Rock&) const;

    std::deque<std::bitset<7>> _chamber            = { 0b1111111 };
    unsigned int               _chamber_height     = 0;
    Cycler<std::vector, char>  _direction_provider;
    char                        _previous_direction = 0;
    bool                        _print_enabled = false;
};

}