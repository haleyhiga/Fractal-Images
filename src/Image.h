#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <vector>

class Image {

public:
    
    Image( ); // default sets x = 0, y = 0
    Image( const int& height, const int& width );

    // methods of the class
    int getHeight( ) const;
    int getWidth( ) const;
    bool indexValid( const int& row, const int& column, const int& channel ) const;
    int index( const int& row, const int& column, const int& channel ) const;
    int getChannel( const int& row, const int& column, const int& channel ) const;
    void setHeight( const int& height );
    void setWidth( const int& width );
    void setChannel( const int& row, const int& column, const int& channel, const int& value );

protected:
    int mHeight;
    int mWidth;
    std::vector < double > mData;

};

#endif /* _IMAGE_H_ */

