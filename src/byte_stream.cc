#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

void Writer::push( string data )
{
  for ( char c : data ) {
    if ( buffer_.size() < capacity_ ) {
      buffer_.push_back( c );
      bytes_pushed_++;
    } else {
        break;
    }
  }
}

void Writer::close()
{ is_closed_ = true; }

void Writer::set_error()
{ error_ = true; }

bool Writer::is_closed() const
{ return is_closed_; }

uint64_t Writer::available_capacity() const
{ return capacity_ - static_cast<uint64_t>( buffer_.size() ); }

uint64_t Writer::bytes_pushed() const
{ return bytes_pushed_; }

string_view Reader::peek() const
{
  if ( buffer_.empty() )
    return {};
  return { &buffer_.front(), 1 };
}

bool Reader::is_finished() const
{
  return is_closed_ == true && buffer_.empty();
}

bool Reader::has_error() const
{
  return error_;
}

void Reader::pop( uint64_t len )
{
    if (!is_finished() && !has_error()) {
        for (uint64_t i = 0; i < len; i++) {
            buffer_.pop_front();
            bytes_popped_++;
        }
    }
}

uint64_t Reader::bytes_buffered() const
{
  return static_cast<uint64_t>(buffer_.size());
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_;
}