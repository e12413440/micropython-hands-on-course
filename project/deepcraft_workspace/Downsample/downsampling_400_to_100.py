import pandas as pd
from scipy.signal import butter, filtfilt

# ==============================
# CONFIG
# ==============================

INPUT_FILE = "IMU-Data.data"
OUTPUT_FILE = "imu_100hz.data"

ORIGINAL_HZ = 400
TARGET_HZ = 100

# ==============================
# FILTER FUNCTION
# ==============================

def lowpass_filter(data, cutoff_hz, fs, order=4):
    nyquist = 0.5 * fs
    normal_cutoff = cutoff_hz / nyquist
    b, a = butter(order, normal_cutoff, btype="low", analog=False)
    return filtfilt(b, a, data)

# ==============================
# LOAD DATA
# ==============================

print("Loading CSV...")
df = pd.read_csv(INPUT_FILE)

timestamp_col = df.columns[0]
imu_cols = df.columns[1:]

print(f"Timestamp column: {timestamp_col}")
print(f"IMU columns: {list(imu_cols)}")

decimation_factor = ORIGINAL_HZ // TARGET_HZ

# ==============================
# FILTER IMU ONLY
# ==============================

print("Applying anti-aliasing filter...")

filtered = df.copy()

cutoff = TARGET_HZ / 2 * 0.8

for col in imu_cols:
    filtered[col] = lowpass_filter(df[col].values, cutoff, ORIGINAL_HZ)

# ==============================
# DOWNSAMPLE
# ==============================

print("Downsampling...")

downsampled = filtered.iloc[::decimation_factor].reset_index(drop=True)

# ==============================
# SAVE
# ==============================

downsampled.to_csv(OUTPUT_FILE, index=False)

print("Done!")
print(f"Original samples: {len(df)}")
print(f"Downsampled samples: {len(downsampled)}")