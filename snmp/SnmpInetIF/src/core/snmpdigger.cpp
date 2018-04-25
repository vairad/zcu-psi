#include "snmpdigger.h"

#include <exception>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "snmpconfiguration.h"

/**
 * Method set up SNMPv3 auth params
 * @brief SNMPDigger::setUpAuth
 * @param name
 * @param password
 * @param security
 */
void SNMPDigger::setUpAuth(std::string name, std::string password, SnmpSecurity security)
{
    /* set the SNMP version number */
    session.version = SnmpConfiguration::version;

    /* set the SNMPv3 user name */
    session.securityName = strdup(name.c_str());
    session.securityNameLen = strlen(session.securityName);

    /* set the security level to authenticated, but not encrypted */
    session.securityLevel = SnmpConfiguration::securityLevel;

    /* set the authentication method */
    setSecurityProtocol(security);

    if (generate_Ku(session.securityAuthProto,
                    session.securityAuthProtoLen,
                    (u_char *) password.c_str(), strlen(password.c_str()),
                    session.securityAuthKey,
                    &session.securityAuthKeyLen) != SNMPERR_SUCCESS) {
        snmp_perror(name.c_str());
        snmp_log(LOG_ERR,
                 "Error generating Ku from authentication pass phrase. \n");
        throw new std::exception();
    }
}

/**
 * @brief SNMPDigger::getSecurityProtocol
 * @param proto protocol to select
 * @return pointer to selectedprotocol (default is throws exception)
 */
void SNMPDigger::setSecurityProtocol(SnmpSecurity security)
{
    switch (security)
    {
    case MD5:
        session.securityAuthProto = usmHMACMD5AuthProtocol;
        session.securityAuthProtoLen = sizeof(usmHMACMD5AuthProtocol)/sizeof(oid);
        break;
    case SHA1:
        session.securityAuthProto = usmHMACSHA1AuthProtocol;
        session.securityAuthProtoLen = sizeof(usmHMACSHA1AuthProtocol)/sizeof(oid);
        break;
//    case SHA256:  //not cant link
//        session.securityAuthProto = usmHMAC192SHA256AuthProtocol;
//        session.securityAuthProtoLen = sizeof(usmHMAC192SHA256AuthProtocol)/sizeof(oid);
//        break;
//    case SHA512:
//        session.securityAuthProto = usmHMAC384SHA512AuthProtocol;
//        session.securityAuthProtoLen = sizeof(usmHMAC384SHA512AuthProtocol)/sizeof(oid);
//        break;
    }
    session.securityAuthKeyLen = USM_AUTH_KU_LEN;
}

bool SNMPDigger::askSNMPforInteger64(std::string asked_oid, int64_t &number)
{
    netsnmp_pdu *pdu;
    netsnmp_pdu *response;
    oid anOID[MAX_OID_LEN];
    size_t anOID_len;
    int status;
    bool success = false;

    pdu = snmp_pdu_create(SNMP_MSG_GET);

    anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(asked_oid.c_str(), anOID, &anOID_len))
    {
      snmp_perror(asked_oid.c_str());
      std::cerr << "Unknown OID" << asked_oid << std::endl;
      snmp_free_pdu(pdu);
      return false;
    }
    snmp_add_null_var(pdu, anOID, anOID_len);
    status = snmp_synch_response(ss, pdu, &response);

    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR)
    {
        netsnmp_variable_list *variable;
        variable = response->variables;

        if (variable->type == ASN_INTEGER || variable->type == ASN_COUNTER)
        {
            number = *variable->val.integer;
            success = true;
        }
        else
        {
            std::cerr << "Returned value is not INTEGER" << std::endl;
            success = false;
        }

    }
    else
    {
        // FAILURE: print what went wrong!
        if (status == STAT_SUCCESS)
            std::cerr << "Error in packet Reason: " << snmp_errstring(response->errstat) << std::endl;
        else if (status == STAT_TIMEOUT)
            std::cerr << "Timeout: No response from: " << session.peername << std::endl;
        else
            snmp_sess_perror("SnmpShowIP", ss);

        success = false;
    }

    // 1) free the response.
    if (response)
    {
        snmp_free_pdu(response);
    }
    return success;
}

bool SNMPDigger::askSNMPforString(std::string asked_oid, std::string &string, bool hex)
{
    netsnmp_pdu *pdu;
    netsnmp_pdu *response;
    oid anOID[MAX_OID_LEN];
    size_t anOID_len;
    int status;
    bool success = false;

    pdu = snmp_pdu_create(SNMP_MSG_GET);

    anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(asked_oid.c_str(), anOID, &anOID_len))
    {
      snmp_perror(asked_oid.c_str());
      std::cerr << "Unknown OID" << asked_oid << std::endl;
      snmp_free_pdu(pdu);
      return false;
    }
    snmp_add_null_var(pdu, anOID, anOID_len);
    status = snmp_synch_response(ss, pdu, &response);

    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR)
    {
        netsnmp_variable_list *variable;
        variable = response->variables;

        if (variable->type == ASN_OCTET_STR)
        {
            u_char *tmpS = (u_char *)malloc(1 + variable->val_len);
            memcpy(tmpS, variable->val.string, variable->val_len);
            tmpS[variable->val_len] = 0 ;
            std::stringstream ss;
            const char* separator = "";
            for(int i=0 ; i < variable->val_len; i++ )
            {
               int val = tmpS[i];
               if(hex){
                   ss << separator <<std::setfill('0') << std::setw(2) << std::hex << val;
                   separator = ":" ;
               }else{
                   ss << tmpS[i];
                   separator = "." ;
               }

            }
            string = ss.str();
            success = true;
            free(tmpS);
        }
        else
        {
            std::cerr << "Returned value is not STRING" << std::endl;
            success = false;
        }
    }
    else
    {
        // FAILURE: print what went wrong!
        if (status == STAT_SUCCESS)
            std::cerr << "Error in packet Reason: " << snmp_errstring(response->errstat) << std::endl;
        else if (status == STAT_TIMEOUT)
            std::cerr << "Timeout: No response from: " << session.peername << std::endl;
        else
            snmp_sess_perror("SnmpShowIP", ss);

        throw new std::exception();

        success = false;
    }

    // 1) free the response.
    if (response)
    {
        snmp_free_pdu(response);
    }
    return success;
}

bool SNMPDigger::askSNMPQuestion(std::string asked_oid)
{

    netsnmp_pdu *pdu;
    netsnmp_pdu *response;
    oid anOID[MAX_OID_LEN];
    size_t anOID_len;
    int status;
    bool success = false;

    pdu = snmp_pdu_create(SNMP_MSG_GET);
    anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(asked_oid.c_str(), anOID, &anOID_len))
    {
      snmp_perror(asked_oid.c_str());
      return false;
    }
//#if OTHER_METHODS
//    /*
//     *  These are alternatives to the 'snmp_parse_oid' call above,
//     *    e.g. specifying the OID by name rather than numerically.
//     */
//    read_objid(".1.3.6.1.2.1.2.2", anOID, &anOID_len);
//    get_node("sysDescr.0", anOID, &anOID_len);
//    read_objid("system.sysDescr.0", anOID, &anOID_len);
//#endif

    snmp_add_null_var(pdu, anOID, anOID_len);

    /*
     * Send the Request out.
     */
    status = snmp_synch_response(ss, pdu, &response);

    /*
    * Process the response.
    */
    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR)
    {

    //for(vars = response->variables; vars; vars = vars->next_variable)
    //print_variable(vars->name, vars->name_length, vars);
            netsnmp_variable_list *vars;
            int count;
        /* manipuate the information ourselves */
        for(vars = response->variables; vars; vars = vars->next_variable)
        {
            if (vars->type == ASN_OCTET_STR)
            {
                char *sp = (char *)malloc(1 + vars->val_len);
                memcpy(sp, vars->val.string, vars->val_len);
                sp[vars->val_len] = '\0';
                printf("value #%d is a string: %s\n", count++, sp);
                free(sp);
            }
            else if (vars->type == ASN_INTEGER)
            {
                char *sp = (char *)malloc(1 + vars->val_len);
                memcpy(sp, vars->val.string, vars->val_len);
                sp[vars->val_len] = '\0';
                printf("value #%d is a number: %s\n", count++, vars->val.integer);
                free(sp);
            }
            else
            {
                printf("value #%d is NOT a string! Ack!\n", count++);
            }

        }
    }
    else
    {
        // FAILURE: print what went wrong!
        if (status == STAT_SUCCESS)
            fprintf(stderr, "Error in packet\nReason: %s\n",
                snmp_errstring(response->errstat));
        else if (status == STAT_TIMEOUT)
            fprintf(stderr, "Timeout: No response from %s.\n",
                session.peername);
        else
            snmp_sess_perror("SnmpShowIP", ss);

    }

    // 1) free the response.
    if (response)
    {
        snmp_free_pdu(response);
    }
}

SNMPDigger::SNMPDigger(SnmpConnectionDetails *details):
    connectionDetails(details)
{
    // Initialize the SNMP library
        init_snmp("SnmpShowIP");

    // Initialize a "session" that defines who we're going to talk to
        snmp_sess_init( &session );                   /* set up defaults */
        session.peername = strdup(details->getHostname().c_str());

        setUpAuth(details->getUsername(), details->getPassword(), details->getSecurity());

    //Establish session
        SOCK_STARTUP;
        ss = snmp_open(&session);                     /* establish the session */

        if (!ss) {
          snmp_sess_perror("ack", &session);
          SOCK_CLEANUP;
          throw new std::exception();
        }
}

SNMPDigger::~SNMPDigger()
{
    //Clean up - close session
    SOCK_CLEANUP;
}
