
#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <map>
#include "request.hpp"
#include "response_line.hpp"
#include "response_header.hpp"
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include "config_file.hpp"

#define DIR 1
#define FILE 0
#define OFF 0
class Response
{
    public :
        Response();
        Response(Request);
        
        const HttpResponseLine&     getResponseLine() const;
        const HttpResponseHeader&   getResponseHeader() const;
        const std::string&          getBody() const;

        const std::string&          getResponse() const;

        ServerConfig&               getMacthedServer(std::string&);
        void                        getMacthedLocation(std::string);
        
        void                        handleRequest(int fd);
        void                        setConfig(std::vector<ServerConfig>&);


        void                        set_location_vars();

        //|=====Errors check======|
        void                         is_location_have_redirection();
        void                         checkHttpVersion(const std::string&);
        void                         checkMethodValidity(const std::string&,std::vector<std::string>&);
        // int                         isUriTooLong(int&);
        void                         checkBodySize(const unsigned long&, int);

        void                         handleGetMethod();
        int                          get_resource_type(std::string&);

        //|=======================|

        //|=====GET METHOD======|
        
        int     checkPathInRoot(std::string&);
        int     getResourceType(std::string&);
        int     isDirHasIndexFiles();
        int     getAutoIndex();
        int     isUriHasSlashInend(const std::string&);
        //|=======================|

    private :


        Request             _request;
        HttpResponseLine    _response_line;
        HttpResponseHeader  _response_header;
        std::string         _body;
        std::string         _response;
        std::vector<ServerConfig> _config_vec;
        ServerConfig        _conf;
        std::vector<LOCATION_PAIR >   _locations;
        DIRS_PAIR location_dirs;

        DIRS_PAIR       _directives;
        std::vector<std::string> _http_versions;
        std::vector<std::string> _http_methods;
};

#endif