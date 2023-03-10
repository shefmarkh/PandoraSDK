/**
 *  @file   PandoraSDK/include/Pandora/PandoraInputTypes.h
 * 
 *  @brief  Header file for pandora input types and associated external typedefs exposed via the PandoraApi
 * 
 *  $Log: $
 */
#ifndef PANDORA_INPUT_TYPES_H
#define PANDORA_INPUT_TYPES_H 1

#include "Objects/CartesianVector.h"
#include "Objects/TrackState.h"

#include "Pandora/PandoraInternal.h"
#include "Pandora/PandoraEnumeratedTypes.h"
#include "Pandora/StatusCodes.h"

#include <cmath>
#include <string>
#include <vector>

namespace pandora
{

/**
 *  @brief  PandoraInputType template class
 */
template <typename T>
class PandoraInputType
{
public:
    /**
     *  @brief  Default constructor
     */
    PandoraInputType();

    /**
     *  @brief  Destructor
     */
    ~PandoraInputType();

    /**
     *  @brief  Constructor
     *
     *  @param  t the initial value
     */
    PandoraInputType(const T &t);

    /**
     *  @brief  Copy constructor (EXPENSIVE WITH LARGE OBJECTS)
     * 
     *  @param  rhs the initial pandora type
     */
    PandoraInputType(const PandoraInputType<T> &rhs);

    /**
     *  @brief  Set the value held by the pandora type
     *
     *  @param  t the value
     */
    void Set(const T &t);

    /**
     *  @brief  Get the value held by the pandora type
     *
     *  @return the value
     */
    const T &Get() const;

    /**
     *  @brief  Reset the pandora type
     */   
    void Reset();

    /**
     *  @brief  Whether the pandora type is initialized
     *
     *  @return boolean
     */
    bool IsInitialized() const;

    /**
     *  @brief  Assignment operator for the pandora type
     * 
     *  @return whether assignment succeeded
     */
    bool operator= (const T &rhs); 

    /**
     *  @brief  Assignment operator for parent pandora type (EXPENSIVE WITH LARGE OBJECTS)
     * 
     *  @throw  status code exception
     */   
    bool operator= (const PandoraInputType<T> &rhs);

private:
    /**
     *  @brief  Whether pandora type is valid (not inf or nan)
     * 
     *  @return boolean
     */
    bool IsValid(const T &t) const;

    T      *m_pValue;           ///< Address of the actual value being held by the pandora type
    bool    m_isInitialized;    ///< Whether the pandora type is initialized
};

//------------------------------------------------------------------------------------------------------------------------------------------

typedef PandoraInputType<unsigned int> InputUInt;
typedef PandoraInputType<int> InputInt;
typedef PandoraInputType<float> InputFloat;
typedef PandoraInputType<const void *> InputAddress;
typedef PandoraInputType<bool> InputBool;
typedef PandoraInputType<std::string> InputString;

typedef PandoraInputType<CellGeometry> InputCellGeometry;
typedef PandoraInputType<HitRegion> InputHitRegion;
typedef PandoraInputType<HitType> InputHitType;
typedef PandoraInputType<LineGapType> InputLineGapType;
typedef PandoraInputType<MCParticleType> InputMCParticleType;
typedef PandoraInputType<SubDetectorType> InputSubDetectorType;
typedef PandoraInputType<VertexLabel> InputVertexLabel;
typedef PandoraInputType<VertexType> InputVertexType;

typedef PandoraInputType<CartesianVector> InputCartesianVector;
typedef PandoraInputType<TrackState> InputTrackState;
typedef PandoraInputType<const Track *> InputTrackAddress;

typedef std::vector<const void *> CaloHitAddressList, TrackAddressList;
typedef std::vector<CaloHitAddressList> ClusterAddressList;

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline PandoraInputType<T>::PandoraInputType() :
    m_pValue(nullptr),
    m_isInitialized(false)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline PandoraInputType<T>::~PandoraInputType()
{
    if (nullptr != m_pValue)
        delete m_pValue;
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline PandoraInputType<T>::PandoraInputType(const T &t) :
    m_pValue(new T(t)),
    m_isInitialized(true)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline PandoraInputType<T>::PandoraInputType(const PandoraInputType<T> &rhs) :
    m_pValue(nullptr),
    m_isInitialized(rhs.m_isInitialized)
{
    if (rhs.m_isInitialized)
        m_pValue = new T(*rhs.m_pValue);
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline void PandoraInputType<T>::Set(const T &t)
{
    if (m_isInitialized)
        delete m_pValue;

    if (!this->IsValid(t))
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

    m_pValue = new T(t);
    m_isInitialized = true;
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline const T &PandoraInputType<T>::Get() const
{
    if (!m_isInitialized)
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    return *m_pValue;
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline void PandoraInputType<T>::Reset()
{
    if (nullptr != m_pValue)
        delete m_pValue;

    m_isInitialized = false;
    m_pValue = nullptr;
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool PandoraInputType<T>::IsInitialized() const
{
    return m_isInitialized;
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool PandoraInputType<T>::operator= (const T &rhs)
{
    this->Set(rhs);
    return m_isInitialized;
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool PandoraInputType<T>::operator= (const PandoraInputType<T> &rhs)
{
    if (this == &rhs)
        return m_isInitialized;

    if (rhs.m_isInitialized)
    {
        this->Set(*rhs.m_pValue);
    }
    else
    {
        this->Reset();
    }

    return m_isInitialized;
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool PandoraInputType<T>::IsValid(const T &t) const
{
    return !(std::isnan(t) || std::isinf(t));
}

template <>
inline bool PandoraInputType<const void *>::IsValid(const void *const &) const
{
    return true;
}

template <>
inline bool PandoraInputType<const CaloHit *>::IsValid(const CaloHit *const &) const
{
    return true;
}

template <>
inline bool PandoraInputType<const Track *>::IsValid(const Track *const &) const
{
    return true;
}

template <>
inline bool PandoraInputType<CellGeometry>::IsValid(const CellGeometry &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<HitRegion>::IsValid(const HitRegion &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<HitType>::IsValid(const HitType &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<LineGapType>::IsValid(const LineGapType &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<MCParticleType>::IsValid(const MCParticleType &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<SubDetectorType>::IsValid(const SubDetectorType &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<VertexLabel>::IsValid(const VertexLabel &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<VertexType>::IsValid(const VertexType &t) const
{
    return !(std::isnan(static_cast<unsigned int>(t)) || std::isinf(static_cast<unsigned int>(t)));
}

template <>
inline bool PandoraInputType<std::string>::IsValid(const std::string &t) const
{
    return !t.empty();
}

template <>
inline bool PandoraInputType<CartesianVector>::IsValid(const CartesianVector &t) const
{
    return !(std::isnan(t.GetX()) || std::isnan(t.GetY()) || std::isnan(t.GetZ()) ||
        std::isinf(t.GetX()) || std::isinf(t.GetY()) || std::isinf(t.GetZ()));
}

template <>
inline bool PandoraInputType<TrackState>::IsValid(const TrackState &t) const
{
    const CartesianVector &p(t.GetPosition());
    const CartesianVector &m(t.GetMomentum());

    return !(std::isnan(p.GetX()) || std::isnan(p.GetY()) || std::isnan(p.GetZ()) ||
        std::isinf(p.GetX()) || std::isinf(p.GetY()) || std::isinf(p.GetZ()) ||
        std::isnan(m.GetX()) || std::isnan(m.GetY()) || std::isnan(m.GetZ()) ||
        std::isinf(m.GetX()) || std::isinf(m.GetY()) || std::isinf(m.GetZ()));
}

} // namespace pandora

#endif // #ifndef PANDORA_INPUT_TYPES_H
