inputfile=$1

#cat ${inputfile} |grep -v include | sed -e "s/string/std::string/g"  |  sed -e "s/map/std::map/g"  |sed -e "s/vector/std::vector/g"> x
#cat ${inputfile} | sed -e "s/Trim/Trim_/g"  > x
cat ${inputfile} | sed -e "s/ArgvContext/limonp::ArgvContext/g" | sed -e "s/BoundedQueue/limonp::BoundedQueue/g" | sed -e "s/ClosureInterface/limonp::ClosureInterface/g" | sed -e "s/Config/limonp::Config/g"    | sed -e "s/FileLock/limonp::FileLock/g"    | sed -e "s/LocalVector/limonp::LocalVector/g"    | sed -e "s/Logger/limonp::Logger/g" | sed -e "s/MD5/limonp::MD5/g" | sed -e "s/MutexLockGuard/limonp::MutexLockGuard/g" | sed -e "s/NonCopyable/limonp::NonCopyable/g" | sed -e "s/Worker/limonp::Worker/g"   > x
mv x ${inputfile}


