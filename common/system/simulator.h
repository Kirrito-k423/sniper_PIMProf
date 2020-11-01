#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "config.h"
#include "log.h"
#include "inst_mode.h"

#include <decoder.h>

// [Yizhou]
#include "pimprof_datareuse.h"
// [Yizhou] early include
#include "core_manager.h"
#include "thread_manager.h"
#include "thread.h"

class _Thread;
class SyscallServer;
class SyncServer;
class MagicServer;
class ClockSkewMinimizationServer;
class StatsManager;
class Transport;
class CoreManager;
class Thread;
class ThreadManager;
class ThreadStatsManager;
class SimThreadManager;
class HooksManager;
class ClockSkewMinimizationManager;
class FastForwardPerformanceManager;
class TraceManager;
class DvfsManager;
class SamplingManager;
class FaultinjectionManager;
class TagsManager;
class RoutineTracer;
class MemoryTracker;
namespace config { class Config; }

class Simulator
{
public:
   Simulator();
   ~Simulator();

   void start();

   static Simulator* getSingleton() { return m_singleton; }
   static void setConfig(config::Config * cfg, Config::SimulationMode mode);
   static void allocate();
   static void release();

   SyscallServer* getSyscallServer() { return m_syscall_server; }
   SyncServer* getSyncServer() { return m_sync_server; }
   MagicServer* getMagicServer() { return m_magic_server; }
   ClockSkewMinimizationServer* getClockSkewMinimizationServer() { return m_clock_skew_minimization_server; }
   CoreManager *getCoreManager() { return m_core_manager; }
   SimThreadManager *getSimThreadManager() { return m_sim_thread_manager; }
   ThreadManager *getThreadManager() { return m_thread_manager; }
   ClockSkewMinimizationManager *getClockSkewMinimizationManager() { return m_clock_skew_minimization_manager; }
   FastForwardPerformanceManager *getFastForwardPerformanceManager() { return m_fastforward_performance_manager; }
   Config *getConfig() { return &m_config; }
   config::Config *getCfg() {
      //if (! m_config_file_allowed)
      //   LOG_PRINT_ERROR("getCfg() called after init, this is not nice\n");
      return m_config_file;
   }
   void hideCfg() { m_config_file_allowed = false; }
   StatsManager *getStatsManager() { return m_stats_manager; }
   ThreadStatsManager *getThreadStatsManager() { return m_thread_stats_manager; }
   DvfsManager *getDvfsManager() { return m_dvfs_manager; }
   HooksManager *getHooksManager() { return m_hooks_manager; }
   SamplingManager *getSamplingManager() { return m_sampling_manager; }
   FaultinjectionManager *getFaultinjectionManager() { return m_faultinjection_manager; }
   TraceManager *getTraceManager() { return m_trace_manager; }
   TagsManager *getTagsManager() { return m_tags_manager; }
   RoutineTracer *getRoutineTracer() { return m_rtn_tracer; }
   MemoryTracker *getMemoryTracker() { return m_memory_tracker; }
   void setMemoryTracker(MemoryTracker *memory_tracker) { m_memory_tracker = memory_tracker; }

   bool isRunning() { return m_running; }
   static void enablePerformanceModels();
   static void disablePerformanceModels();

   void setInstrumentationMode(InstMode::inst_mode_t new_mode, bool update_barrier);
   InstMode::inst_mode_t getInstrumentationMode() { return InstMode::inst_mode; }

   // Access to the Decoder library for the simulator run
   void createDecoder();
   dl::Decoder *getDecoder();

private:
   Config m_config;
   Log m_log;
   TagsManager *m_tags_manager;
   SyscallServer *m_syscall_server;
   SyncServer *m_sync_server;
   MagicServer *m_magic_server;
   ClockSkewMinimizationServer *m_clock_skew_minimization_server;
   StatsManager *m_stats_manager;
   Transport *m_transport;
   CoreManager *m_core_manager;
   ThreadManager *m_thread_manager;
   ThreadStatsManager *m_thread_stats_manager;
   SimThreadManager *m_sim_thread_manager;
   ClockSkewMinimizationManager *m_clock_skew_minimization_manager;
   FastForwardPerformanceManager *m_fastforward_performance_manager;
   TraceManager *m_trace_manager;
   DvfsManager *m_dvfs_manager;
   HooksManager *m_hooks_manager;
   SamplingManager *m_sampling_manager;
   FaultinjectionManager *m_faultinjection_manager;
   RoutineTracer *m_rtn_tracer;
   MemoryTracker *m_memory_tracker;

   bool m_running;
   bool m_inst_mode_output;

   static Simulator *m_singleton;

   static config::Config *m_config_file;
   static bool m_config_file_allowed;
   static Config::SimulationMode m_mode;
   
   // Object to access the decoder library with the correct configuration
   static dl::Decoder *m_decoder;
   // Surrogate to create a Decoder object for a specific architecture
   dl::DecoderFactory *m_factory;

   void printInstModeSummary();

/* ===================================================================== */
/* [Yizhou] PIMProf Related Code */
/* ===================================================================== */
protected:

   std::vector<PIMProf::PIMProfThreadStats *> m_pimprof_thread_stats;

   // // store the mapping between cache tags and data reuse segments
   // std::unordered_map<uint64_t, PIMProf::DataReuseSegment> m_tag_seg_map;

   // // trie for storing data reuse chains
   // PIMProf::DataReuse m_data_reuse;
public:
   bool PIMProfIsUsingPIM();
   int64_t PIMProfGetCurrentBBLID();
   PIMProf::UUID PIMProfGetCurrentBBLHash();

   void PIMProfBBLStart(uint64_t hi, uint64_t lo);
   void PIMProfBBLEnd(uint64_t hi, uint64_t lo);

   void PIMProfOffloadStart(uint64_t hi, uint64_t type);
   void PIMProfOffloadEnd(uint64_t hi, uint64_t type);

   void PIMProfAddTimeInstruction(uint64_t time, uint64_t instr);
   void PIMProfAddMemory(uint64_t memory_access);

   void PIMProfAddOffloadingTime(uint64_t time);

   void PIMProfDumpStats();

   void PIMProfInsertSegOnHit(uint64_t tag, Core::mem_op_t mem_op_type);
   void PIMProfSplitSegOnMiss(uint64_t tag);

};

__attribute__((unused)) static Simulator *Sim()
{
   return Simulator::getSingleton();
}

#endif // SIMULATOR_H
