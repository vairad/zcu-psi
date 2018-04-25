#include "snmpprocess.h"

#include <thread>
#include <list>
#include <iostream>
#include <unistd.h>
#include <exception>

#include "oiddefinitions.h"
#include "inetinterface.h"
#include "core/coreinterface.h"

std::mutex SnmpProcess::mtx;

bool SnmpProcess::runningThread = false;

/**
 * Method updates structure of ip interfaces on remote device
 * @brief SnmpProcess::updateStructure
 */
void SnmpProcess::updateStructure(SnmpProcess *process)
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        runningThread = true;
    }
    //CoreInterface::fail_msg = "";
    //CoreInterface::fail = false;

   std::cout << "Thread updating values" << std::endl;
   std::list<InetInterface *> interfaces;

   std::string interfacenumber_oid = base_oid + ".1.0";
   int64_t number;
   bool resutl = process->digger->askSNMPforInteger64(interfacenumber_oid, number);

   if(!resutl)
   {
       std::lock_guard<std::mutex> lock(mtx);
       runningThread = false;
       //CoreInterface::fail_msg = "Error connecting host.";
       //CoreInterface::fail = true;
   }

   for (size_t index = 1; index <= number; ++index) {
        interfaces.push_back(lookupInterface(index, process));
   }

   process->state->cleanCollection();
   process->state->append(interfaces);

    {
       std::lock_guard<std::mutex> lock(mtx);
       runningThread = false;
    }
}

InetInterface *SnmpProcess::lookupInterface(size_t index, SnmpProcess *process)
{
    InetInterface *interface = new InetInterface();

    interface->setName("Interface #"+ std::to_string(index));

    std::string string;
    bool suc = process->digger->askSNMPforString(physAdd_oid + "." + std::to_string(index), string, true);
    if(!suc){throw new std::exception();}
    interface->setHwAdd(string);

    suc = process->digger->askSNMPforString(description_oid + "." + std::to_string(index), string, false);
   if(!suc){throw new std::exception();}
   interface->setDescription(string);

    int64_t number;
    suc = process->digger->askSNMPforInteger64(inBytes_oid + "." + std::to_string(index), number);
    if(!suc){throw new std::exception();}
    interface->setInBytes(std::to_string(number));

    suc = process->digger->askSNMPforInteger64(outBytes_oid + "." + std::to_string(index), number);
    if(!suc){throw new std::exception();}
    interface->setOutBytes(std::to_string(number));

    suc = process->digger->askSNMPforInteger64(MTU_oid + "." + std::to_string(index), number);
    if(!suc){throw new std::exception();}
    interface->setMTU(std::to_string(number));

    suc = process->digger->askSNMPforInteger64(adminStatus_oid + "." + std::to_string(index), number);
    if(!suc){throw new std::exception();}
    interface->setAdminState(number);

    return interface;
}


/**
 * Constrictor prepares connection to snmp host depending to connectionDetails.
 * @brief SnmpProcess::SnmpProcess
 * @param connectionDetails
 */
SnmpProcess::SnmpProcess(SnmpConnectionDetails *connectionDetails)
{
    digger = new SNMPDigger(connectionDetails);
    state = SnmpState::getInstance();
}

bool SnmpProcess::update()
{
    std::thread *th_p;
    {
        std::lock_guard<std::mutex> lock(mtx);
        if(runningThread)
        {
            return false;
        }

        th_p = new std::thread(updateStructure, this);
    }
    return true;
}

bool SnmpProcess::isRunning()
{
    std::lock_guard<std::mutex> lock(mtx);
    return runningThread ;
}
