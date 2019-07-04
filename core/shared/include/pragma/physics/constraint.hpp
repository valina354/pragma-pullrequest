#ifndef __PHYSCONSTRAINT_H__
#define __PHYSCONSTRAINT_H__

#include "pragma/networkdefinitions.h"
#include <memory>
#include <sharedutils/def_handle.h>
#include <pragma/physics/physapi.h>
#include "pragma/physics/base.hpp"
#include "pragma/physics/transform.hpp"
#include "pragma/lua/baseluaobj.h"
#include <vector>

namespace pragma
{
	enum class Axis : uint8_t;
	enum class RotationOrder : uint16_t;
};
namespace pragma::physics
{
	class IEnvironment;
	class IRigidBody;
	class DLLNETWORK IConstraint
		: public IBase
	{
	public:
		virtual void OnRemove() override;
		virtual void Initialize()=0;
		virtual void SetEnabled(bool b)=0;
		virtual bool IsEnabled() const=0;
		void SetCollisionsEnabled(Bool b);
		Bool GetCollisionsEnabled() const;
		virtual void EnableCollisions()=0;
		virtual void DisableCollisions()=0;
		virtual pragma::physics::IRigidBody *GetSourceObject()=0;
		virtual pragma::physics::IRigidBody *GetTargetObject()=0;
		Transform &GetSourceTransform();
		Transform &GetTargetTransform();
		Vector3 GetSourcePosition();
		Quat GetSourceRotation();
		Vector3 GetTargetPosition();
		Quat GetTargetRotation();

		virtual void SetOverrideSolverIterationCount(int32_t count)=0;
		virtual int32_t GetOverrideSolverIterationCount() const=0;
		virtual float GetBreakingImpulseThreshold() const=0;
		virtual void SetBreakingImpulseThreshold(float threshold)=0;
	protected:
		IConstraint(IEnvironment &env);
		virtual void DoSetCollisionsEnabled(Bool b)=0;
		Transform m_srcTransform;
		Transform m_tgtTransform;
	private:
		bool m_bCollisionsEnabled = true;
	};

	class DLLNETWORK IFixedConstraint
		: virtual public IConstraint
	{
	protected:
		using IConstraint::IConstraint;
	};

	class DLLNETWORK IBallSocketConstraint
		: virtual public IConstraint
	{
	protected:
		using IConstraint::IConstraint;
	};

	class DLLNETWORK IHingeConstraint
		: virtual public IConstraint
	{
	protected:
		using IConstraint::IConstraint;
	};

	class DLLNETWORK ISliderConstraint
		: virtual public IConstraint
	{
	protected:
		using IConstraint::IConstraint;
	};

	class DLLNETWORK IConeTwistConstraint
		: virtual public IConstraint
	{
	protected:
		using IConstraint::IConstraint;
	public:
		virtual void SetLimit(float swingSpan1,float swingSpan2,float twistSpan,float softness=1.f,float biasFactor=0.3f,float relaxationFactor=1.f)=0;
	};

	class DLLNETWORK IDoFConstraint
		: virtual public IConstraint
	{
	protected:
		using IConstraint::IConstraint;
	public:
		virtual void SetLinearLimit(const Vector3 &lower,const Vector3 &upper)=0;
		virtual void SetLinearLimit(const Vector3 &lim)=0;
		virtual void SetLinearLowerLimit(const Vector3 &lim)=0;
		virtual void SetLinearUpperLimit(const Vector3 &lim)=0;
		virtual void SetAngularLimit(const EulerAngles &lower,const EulerAngles &upper)=0;
		virtual void SetAngularLimit(const EulerAngles &lim)=0;
		virtual void SetAngularLowerLimit(const EulerAngles &lim)=0;
		virtual void SetAngularUpperLimit(const EulerAngles &lim)=0;

		virtual Vector3 GetLinearLowerLimit() const=0;
		virtual Vector3 GetlinearUpperLimit() const=0;
		virtual EulerAngles GetAngularLowerLimit() const=0;
		virtual EulerAngles GetAngularUpperLimit() const=0;

		virtual Vector3 GetAngularTargetVelocity() const=0;
		virtual void SetAngularTargetVelocity(const Vector3 &vel) const=0;
		virtual Vector3 GetAngularMaxMotorForce() const=0;
		virtual void SetAngularMaxMotorForce(const Vector3 &force)=0;
		virtual Vector3 GetAngularMaxLimitForce() const=0;
		virtual void SetAngularMaxLimitForce(const Vector3 &force)=0;
		virtual Vector3 GetAngularDamping() const=0;
		virtual void SetAngularDamping(const Vector3 &damping)=0;
		virtual Vector3 GetAngularLimitSoftness() const=0;
		virtual void SetAngularLimitSoftness(const Vector3 &softness)=0;
		virtual Vector3 GetAngularForceMixingFactor() const=0;
		virtual void SetAngularForceMixingFactor(const Vector3 &factor)=0;
		virtual Vector3 GetAngularLimitErrorTolerance() const=0;
		virtual void SetAngularLimitErrorTolerance(const Vector3 &tolerance)=0;
		virtual Vector3 GetAngularLimitForceMixingFactor() const=0;
		virtual void SetAngularLimitForceMixingFactor(const Vector3 &factor)=0;
		virtual Vector3 GetAngularRestitutionFactor() const=0;
		virtual void SetAngularRestitutionFactor(const Vector3 &factor)=0;
		virtual bool IsAngularMotorEnabled(uint8_t axis) const=0;
		virtual void SetAngularMotorEnabled(uint8_t axis,bool bEnabled)=0;
		virtual Vector3 GetCurrentAngularLimitError() const=0;
		virtual Vector3 GetCurrentAngularPosition() const=0;
		virtual Vector3i GetCurrentAngularLimit() const=0;
		virtual Vector3 GetCurrentAngularAccumulatedImpulse() const=0;

		virtual Vector3 GetLinearTargetVelocity() const=0;
		virtual void SetLinearTargetVelocity(const Vector3 &vel) const=0;
		virtual Vector3 GetLinearMaxMotorForce() const=0;
		virtual void SetLinearMaxMotorForce(const Vector3 &force)=0;
		virtual float GetLinearDamping() const=0;
		virtual void SetLinearDamping(float damping)=0;
		virtual float GetLinearLimitSoftness() const=0;
		virtual void SetLinearLimitSoftness(float softness)=0;
		virtual Vector3 GetLinearForceMixingFactor() const=0;
		virtual void SetLinearForceMixingFactor(const Vector3 &factor)=0;
		virtual Vector3 GetLinearLimitErrorTolerance() const=0;
		virtual void SetLinearLimitErrorTolerance(const Vector3 &tolerance)=0;
		virtual Vector3 GetLinearLimitForceMixingFactor() const=0;
		virtual void SetLinearLimitForceMixingFactor(const Vector3 &factor)=0;
		virtual float GetLinearRestitutionFactor() const=0;
		virtual void SetLinearRestitutionFactor(float factor)=0;
		virtual bool IsLinearMotorEnabled(uint8_t axis) const=0;
		virtual void SetLinearMotorEnabled(uint8_t axis,bool bEnabled)=0;
		virtual Vector3 GetCurrentLinearDifference() const=0;
		virtual Vector3 GetCurrentLinearLimitError() const=0;
		virtual Vector3i GetCurrentLinearLimit() const=0;
		virtual Vector3 GetCurrentLinearAccumulatedImpulse() const=0;
	};

	class DLLNETWORK IDoFSpringConstraint
		: virtual public IConstraint
	{
	protected:
		using IConstraint::IConstraint;
	public:
		enum class AxisType : uint8_t
		{
			Linear = 0u,
			Angular
		};

		virtual void CalculateTransforms()=0;
		virtual void CalculateTransforms(const Transform &frameA,const Transform &frameB)=0;
		virtual Transform GetCalculatedTransformA() const=0;
		virtual Transform GetCalculatedTransformB() const=0;
		virtual Transform GetFrameOffsetA() const=0;
		virtual Transform GetFrameOffsetB() const=0;
		virtual Vector3 GetAxis(pragma::Axis axisIndex) const=0;
		virtual double GetAngle(pragma::Axis axisIndex) const=0;
		virtual double GetRelativePivotPosition(pragma::Axis axisIndex) const=0;
		virtual void SetFrames(const Transform &frameA,const Transform &frameB)=0;
		virtual void SetLinearLowerLimit(const Vector3 &linearLower)=0;
		virtual Vector3 GetLinearLowerLimit() const=0;
		virtual void SetLinearUpperLimit(const Vector3 &linearUpper)=0;
		virtual Vector3 GetLinearUpperLimit() const=0;
		virtual void SetAngularLowerLimit(const Vector3 &angularLower)=0;
		virtual void SetAngularLowerLimitReversed(const Vector3 &angularLower)=0;
		virtual Vector3 GetAngularLowerLimit() const=0;
		virtual Vector3 GetAngularLowerLimitReversed() const=0;
		virtual void SetAngularUpperLimit(const Vector3 &angularUpper)=0;
		virtual void SetAngularUpperLimitReversed(const Vector3 &angularUpper)=0;
		virtual Vector3 GetAngularUpperLimit() const=0;
		virtual Vector3 GetAngularUpperLimitReversed() const=0;
		virtual void SetLimit(AxisType type,pragma::Axis axis,double lo,double hi)=0;
		virtual void SetLimitReversed(AxisType type,pragma::Axis axis,double lo,double hi)=0;
		virtual bool IsLimited(AxisType type,pragma::Axis axis) const=0;
		virtual void SetRotationOrder(pragma::RotationOrder order)=0;
		virtual pragma::RotationOrder GetRotationOrder() const=0;
		virtual void SetAxis(const Vector3 &axis1,const Vector3 &axis2)=0;
		virtual void SetBounce(AxisType type,pragma::Axis axis,double bounce)=0;
		virtual void EnableMotor(AxisType type,pragma::Axis axis,bool onOff)=0;
		virtual void SetServo(AxisType type,pragma::Axis axis,bool onOff)=0;
		virtual void SetTargetVelocity(AxisType type,pragma::Axis axis,double velocity)=0;
		virtual void SetServoTarget(AxisType type,pragma::Axis axis,double target)=0;
		virtual void SetMaxMotorForce(AxisType type,pragma::Axis axis,double force)=0;
		virtual void EnableSpring(AxisType type,pragma::Axis axis,bool onOff)=0;
		virtual void SetStiffness(AxisType type,pragma::Axis axis,double stiffness,bool limitIfNeeded=true)=0;
		virtual void SetDamping(AxisType type,pragma::Axis axis,double damping,bool limitIfNeeded=true)=0;
		virtual void SetEquilibriumPoint()=0;
		virtual void SetEquilibriumPoint(AxisType type,pragma::Axis axis)=0;
		virtual void SetEquilibriumPoint(AxisType type,pragma::Axis axis,double val)=0;

		virtual void SetERP(AxisType type,pragma::Axis axis,double value)=0;
		virtual double GetERP(AxisType type,pragma::Axis axis) const=0;
		virtual void SetStopERP(AxisType type,pragma::Axis axis,double value)=0;
		virtual double GetStopERP(AxisType type,pragma::Axis axis) const=0;
		virtual void SetCFM(AxisType type,pragma::Axis axis,double value)=0;
		virtual double GetCFM(AxisType type,pragma::Axis axis) const=0;
		virtual void SetStopCFM(AxisType type,pragma::Axis axis,double value)=0;
		virtual double GetStopCFM(AxisType type,pragma::Axis axis) const=0;
	};
};

#endif
