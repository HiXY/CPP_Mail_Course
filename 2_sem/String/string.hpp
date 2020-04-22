#pragma once

#include <cstdlib>
#include <iostream>

class String
{
    public:
        using CharT = char;
        using size_type = std::size_t;
        static const size_type npos = -1;

        String ();
        String (size_type, CharT);
        String (String const &);
        String (CharT const *);
        ~String ();

        String      &operator = (String const &);
        CharT       &operator[] (size_type);
        CharT const &operator[] (size_type) const;
        CharT       &front ();
        CharT const &front () const;
        CharT       &back ();
        CharT const &back () const;
        CharT const *c_str () const;

        bool      empty () const;
        size_type size () const;
        size_type capacity () const;
        void      reserve (size_type);
        void      resize (size_type);
        void      shrink_to_fit ();

        void      clear ();
        String    &erase (size_type index = 0, size_type count = npos);
        void      push_back (CharT);
        void      pop_back ();
        String    &append (String const &);
        String    &append (CharT const *);
        String    &operator += (String const &);
        String    &operator += (CharT const *);
        int       compare (String const &) const;
        int       compare (CharT const *) const;
        int       compare (size_type pos, size_type count, String const &);
        int       compare (size_type pos, size_type count, CharT const *);
        String    substr (size_type pos = 0, size_type count = npos) const;
        size_type find (CharT) const;
        size_type find (String const &, size_type pos = 0) const;
        size_type find (CharT const *, size_type pos = 0) const;

        bool                operator == (String const &);
        bool                operator == (CharT const *);
        friend bool         operator == (CharT const *, String const &);
        String              operator + (String const &) const;
        String              operator + (CharT const *) const;
        friend String       operator + (CharT const *, String const &);
        friend std::ostream &operator << (std::ostream &, String const &);
        friend std::istream &operator >> (std::istream &, String &);

    private:
        size_type capacity_;
        CharT *data_;
        size_type size_;
};
