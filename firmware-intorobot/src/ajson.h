/**
 ******************************************************************************
 * @file        : ajson.h
 * @author   : robin
 * @version  : V1.0.0
 * @date      : 6-December-2014
 * @brief      :  
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/
#ifndef   AJSON_H_
#define   AJSON_H_

#include "wiring_usartserial.h"
#include "wiring_client.h"
#include "wiring.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/
// aJson Types:
#define aJson_False 0
#define aJson_True 1
#define aJson_NULL 2
#define aJson_Int 3
#define aJson_Float 4
#define aJson_String 5
#define aJson_Array 6
#define aJson_Object 7

#define aJson_IsReference 128

#ifndef EOF
#define EOF -1
#endif

// The aJson structure:
typedef struct aJsonObject 
{
    char *name; // The item's name string, if this item is the child of, or is in the list of subitems of an object.
    struct aJsonObject *next, *prev; // next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem
    struct aJsonObject *child; // An array or object item will have a child pointer pointing to a chain of the items in the array/object.

    char type; // The type of the item, as above.

    union 
    {
        char *valuestring; // The item's string, if type==aJson_String
        char valuebool; //the items value for true & false
        int valueint; // The item's number, if type==aJson_Number
        double valuefloat; // The item's number, if type==aJson_Number
    };
} aJsonObject;

/* aJsonStream is stream representation of aJson for its internal use;
 * it is meant to abstract out differences between Stream (e.g. serial
 * stream) and Client (which may or may not be connected) or provide even
 * stream-ish interface to string buffers. */
class aJsonStream : public Print 
{
    public:
        aJsonStream(Stream *stream_): stream_obj(stream_), bucket(EOF) {}
            /* Use this to check if more data is available, as aJsonStream
            * can read some more data than really consumed and automatically
            * skips separating whitespace if you use this method. */
        virtual bool available(void);

        int parseNumber(aJsonObject *item);
        int printInt(aJsonObject *item);
        int printFloat(aJsonObject *item);

        int parseString(aJsonObject *item);
        int printStringPtr(const char *str);
        int printString(aJsonObject *item);

        int skip(void);
        int flush(void);

        int parseValue(aJsonObject *item, char** filter);
        int printValue(aJsonObject *item);

        int parseArray(aJsonObject *item, char** filter);
        int printArray(aJsonObject *item);

        int parseObject(aJsonObject *item, char** filter);
        int printObject(aJsonObject *item);

    protected:
            /* Blocking load of character, returning EOF if the stream
            * is exhausted. */
            /* Base implementation just looks at bucket, returns EOF
            * otherwise; descendats take care of the real reading. */
        virtual int getch(void);
        virtual size_t readBytes(uint8_t *buffer, size_t len);
            /* Return the character back to the front of the stream
            * after loading it with getch(). Only returning a single
            * character is supported. */
        virtual void ungetch(char ch);

        /* Inherited from class Print. */
        virtual size_t write(uint8_t ch);

            /* stream attribute is used only from virtual functions,
            * therefore an object inheriting aJsonStream may avoid
            * using streams completely. */
        Stream *stream_obj;
            /* Use this accessor for stream retrieval; some subclasses
            * may use their own stream subclass. */
        virtual inline Stream *stream(void) { return stream_obj; }

            /* bucket is EOF by default. Otherwise, it is a character
            * to be returned by next getch() - returned by a call
            * to ungetch(). */
        int bucket;
};

/* JSON stream that is bound to input and output string buffer. This is
 * for internal usage by string-based aJsonClass methods. */
/* TODO: Elastic output buffer support. */
class aJsonStringStream : public aJsonStream 
{
    public:
        /* Either of inbuf, outbuf can be NULL if you do not care about
        * particular I/O direction. */
        aJsonStringStream(char *inbuf_, char *outbuf_ = NULL, size_t outbuf_len_ = 0)
        : aJsonStream(NULL), inbuf(inbuf_), outbuf(outbuf_), outbuf_len(outbuf_len_)
        {
            inbuf_len = inbuf ? strlen(inbuf) : 0;
        }

        virtual bool available(void);

    private:
        virtual int getch(void);
        virtual size_t write(uint8_t ch);

        char *inbuf, *outbuf;
        size_t inbuf_len, outbuf_len;
};


class aJsonClass 
{
        /******************************************************************************
        * Constructors
        ******************************************************************************/

        /******************************************************************************
        * User API
        ******************************************************************************/
    public:
        // Supply a block of JSON, and this returns a aJson object you can interrogate. Call aJson.deleteItem when finished.
        aJsonObject* parse(aJsonStream* stream); //Reads from a stream
        aJsonObject* parse(aJsonStream* stream,char** filter_values); //Read from a file, but only return values include in the char* array filter_values
        aJsonObject* parse(char *value); //Reads from a string
        // Render a aJsonObject entity to text for transfer/storage. Free the char* when finished.
        int print(aJsonObject *item, aJsonStream* stream);
        char* print(aJsonObject* item);
        //Renders a aJsonObject directly to a output stream
        char stream(aJsonObject *item, aJsonStream* stream);
        // Delete a aJsonObject entity and all sub-entities.
        void deleteItem(aJsonObject *c);
        // Returns the number of items in an array (or object).
        unsigned char getArraySize(aJsonObject *array);
        // Retrieve item number "item" from array "array". Returns NULL if unsuccessful.
        aJsonObject* getArrayItem(aJsonObject *array, unsigned char item);
        // Get item "string" from object. Case insensitive.
        aJsonObject* getObjectItem(aJsonObject *object, const char *string);
        // These calls create a aJsonObject item of the appropriate type.
        aJsonObject* createNull(void);
        aJsonObject* createTrue(void);
        aJsonObject* createFalse(void);
        aJsonObject* createItem(char b);
        aJsonObject* createItem(int num);
        aJsonObject* createItem(double num);
        aJsonObject* createItem(const char *string);
        aJsonObject* createArray(void);
        aJsonObject* createObject(void);
        // These utilities create an Array of count items.
        aJsonObject* createIntArray(int *numbers, unsigned char count);
        aJsonObject* createFloatArray(double *numbers, unsigned char count);
        aJsonObject* createDoubleArray(double *numbers, unsigned char count);
        aJsonObject* createStringArray(const char **strings, unsigned char count);
        // Append item to the specified array/object.
        void addItemToArray(aJsonObject *array, aJsonObject *item);
        void addItemToObject(aJsonObject *object, const char *string,aJsonObject *item);
        // Append reference to item to the specified array/object. Use this when you want to add an existing aJsonObject to a new aJsonObject, but don't want to corrupt your existing aJsonObject.
        void addItemReferenceToArray(aJsonObject *array, aJsonObject *item);
        void addItemReferenceToObject(aJsonObject *object, const char *string, aJsonObject *item);
        // Remove/Detach items from Arrays/Objects.
        aJsonObject* detachItemFromArray(aJsonObject *array, unsigned char which);
        void deleteItemFromArray(aJsonObject *array, unsigned char which);
        aJsonObject* detachItemFromObject(aJsonObject *object, const char *string);
        void deleteItemFromObject(aJsonObject *object, const char *string);
        // Update array items.
        void replaceItemInArray(aJsonObject *array, unsigned char which, aJsonObject *newitem);
        void replaceItemInObject(aJsonObject *object, const char *string, aJsonObject *newitem);
        void addNullToObject(aJsonObject* object, const char* name);
        void addBooleanToObject(aJsonObject* object, const char* name, bool b);
        void addTrueToObject(aJsonObject* object, const char* name);
        void addFalseToObject(aJsonObject* object, const char* name);
        void addNumberToObject(aJsonObject* object, const char* name, int n);
        void addNumberToObject(aJsonObject* object, const char* name, double n);
        void addStringToObject(aJsonObject* object, const char* name,const char* s);

    protected:
        friend class aJsonStream;
        static aJsonObject* newItem(void);

    private:
        void suffixObject(aJsonObject *prev, aJsonObject *item);
        aJsonObject* createReference(aJsonObject *item);
};

bool jsonGetValue(uint8_t *payload, const char *string, bool &ret_bool);
bool jsonGetValue(uint8_t *payload, const char *string, char &ret_char);
bool jsonGetValue(uint8_t *payload, const char *string, String &ret_string);
bool jsonGetValue(uint8_t *payload, const char *string, uint8_t &ret_u8);
bool jsonGetValue(uint8_t *payload,  const char *string, short &ret_short);
bool jsonGetValue(uint8_t *payload, const char *string, unsigned short &ret_ushort);
bool jsonGetValue(uint8_t *payload,  const char *string, int &ret_int);
bool jsonGetValue(uint8_t *payload, const char *string, unsigned int &ret_uint);
bool jsonGetValue(uint8_t *payload,  const char *string, long &ret_long);
bool jsonGetValue(uint8_t *payload, const char *string, unsigned long &ret_ulong);
bool jsonGetValue(uint8_t *payload, const char *string, float &ret_float);
bool jsonGetValue(uint8_t *payload, const char *string, double &ret_double);

//
#endif /*AJSON_H_*/

