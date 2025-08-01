#pragma once


#include "config.h"


namespace renderer 
{

	namespace units
	{

		enum class AbsoluteUnits
		{
			Pixels,
			UniversalUnit = Pixels,
			Inches,
			Centimeters,
			Millimeters,
			Points,
			Picas,
		};

		enum class RelativeUnits
		{
			Percent,
			Em,
			Rem,
			Vw,
			Vh,
			Vmin,
			Vmax,
			Ex,
			Ch
		};


		template <AbsoluteUnits T>
		class AbsoluteUnit
		{
		public:

			static AbsoluteUnit& get()
			{
				static AbsoluteUnit instance;
				return instance;
			}

			float get_how_many() const
			{
				return _howMany;
			}

			float get_value() const
			{
				return _value;
			}

			void set_how_many(float value)
			{
				if (value > 0.0f)
				{
					_howMany = value;
					_value = 1.0f / _howMany;
				}
			}

		private:

			AbsoluteUnit() = default;

			float _howMany = 0.0f;

			float _value = 0.0f;

		};
		template <RelativeUnits T>
		class RelativeUnit
		{
		public:
			RelativeUnit() = default;

			void update_value()
			{
				if (_howMany > 0.0f)
					_value = (_referenceValue * _howMany);
				else
					_value = 0.0f;
			}

			float compute_value(float referenceValue, float howMany) const
			{
				if (howMany > 0.0f)
					return referenceValue * howMany;
				else
					return 0.0f;
			}

			void set_reference_value(float ref)
			{
				_referenceValue = ref;
				update_value();
			}

			void set_how_many(float howMany)
			{
				_howMany = howMany;
				update_value();
			}

			float get_computed_value() const
			{
				return _value;
			}

			float get_unit_value() const
			{
				return _howMany;
			}

		private:

			float _referenceValue = 0.0f;
			float _howMany = 0.0f;
			float _value = 0.0f;
		};





		float operator"" _pixels(long double value)
		{
			return value * AbsoluteUnit<AbsoluteUnits::Pixels>::get().get_value();
		}

		float operator"" _inches(long double value)
		{
			return value * AbsoluteUnit<AbsoluteUnits::Inches>::get().get_value();
		}

		float operator"" _centimeters(long double value)
		{
			return value * AbsoluteUnit<AbsoluteUnits::Centimeters>::get().get_value();
		}

		float operator"" _millimeters(long double value)
		{
			return value * AbsoluteUnit<AbsoluteUnits::Millimeters>::get().get_value();
		}

		float operator"" _points(long double value)
		{
			return value * AbsoluteUnit<AbsoluteUnits::Points>::get().get_value();
		}

		float operator"" _picas(long double value)
		{
			return value * AbsoluteUnit<AbsoluteUnits::Picas>::get().get_value();
		}

	}
}